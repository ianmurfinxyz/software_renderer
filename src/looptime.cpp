/*
 * Gameloop Timing Module
 * 
 * Author: Ian Murfin
 */


/* Feature test macro for nanosleep() which is defined in the GNU c library (not
 * the ISO standard). The ISO standard defines no functions for sleeping the 
 * cpu.
 * doc for nanosleep: http://man7.org/linux/man-pages/man2/nanosleep.2.html
 */
#define _POSIX_C_SOURCE 199309L 
#define __DEBUG

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "looptime.h" /*Interface file for this module*/

//==============================================================================
// Private Helpers
//==============================================================================

/* 
 * Calculate interval between two time values.
 * 
 * note: not my code:
 * source: http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
 * 
 * note: this function makes the implicit assumption that end is after start. If
 * end is before start it will return undefined behaviour. This function is used
 * to measure the difference between 2 absolute times, it cannot be used to 
 * measure the difference between 2 elapsed times.
 * 
 * note: technically it can measure the difference between two elapsed times if
 * it is guaranteed that end > start, since you can treat the elapsed times as
 * absolute time values in this case.
 * 
 */
static void diff_t(struct timespec* start, struct timespec* end, struct timespec* ret){
	if((end->tv_nsec - start->tv_nsec) < 0){
		ret->tv_sec = end->tv_sec - start->tv_sec - 1;
		ret->tv_nsec = (1000000000 + (end->tv_nsec - start->tv_nsec));
	} 
    else {
		ret->tv_sec = end->tv_sec - start->tv_sec;
		ret->tv_nsec = end->tv_nsec - start->tv_nsec;
	}
}

/* Measures the difference between 2 elapsed times. Returns the difference in
 * nanoseconds as a long integer.
 * 
 * note: if on a 32-bit system then signed long int is 32 bit and this can hold 
 * a max value of +/-~2.14e9 (i.e 2.14 billion). Since 1 second equals 1 billion 
 * nanoseconds, this means this function cannot be used to get the difference
 * between two elapsed times if the difference is greater than ~2seconds since
 * the signed long int returned would wrap and the result would be wrong.
 */
static long diff_elapsed_ns(struct timespec* dt_0, struct timespec* dt_1){
    long dt0_ns = ((dt_0->tv_sec * 1000000000) + dt_0->tv_nsec);
    long dt1_ns = ((dt_1->tv_sec * 1000000000) + dt_1->tv_nsec);
    return dt1_ns - dt0_ns;
}

/* Measures the difference between 2 elapsed times. Returns the difference in
 * seconds as a double.
 */
static double diff_elapsed_s(struct timespec* dt_0, struct timespec* dt_1){
    double dt0_s = ((double)dt_0->tv_sec  + ((double)dt_0->tv_nsec / 1000000000.0));
    double dt1_s = ((double)dt_1->tv_sec  + ((double)dt_1->tv_nsec / 1000000000.0));
    return dt1_s - dt0_s;
}
 
/* Sleep the thread for the interval passed.
 */
static void sleep_interval(struct timespec* req){
    struct timespec rem;
    if(nanosleep(req, &rem) < 0){
        printf("WARNING: sleep returned early"); /*TODO: handle this better? sleep remainder?*/
    }
}

static void zero_timespec_array(struct timespec* tsa, unsigned int n){
    for(int i = 0; i < n; i++){
        tsa[i].tv_sec = tsa[i].tv_nsec = 0;
    }
}

/* Shifts the array values by 1 place toward higher indices, i.e. "removes"
 * element length-1 and "creates" a new element for index 0.
 * 
 * note: no memory is actually freed or allocated. It is only values which are
 * shifted. The "new" element for index 0 is initialised to 0.
*/
static void shift_timespec_array(struct timespec* tsa, unsigned int n){
    for(int i = n; i >= 1; i--){
        tsa[i].tv_sec = tsa[i-1].tv_sec;
        tsa[i].tv_nsec = tsa[i-1].tv_nsec;
    }
    tsa[0].tv_sec = tsa[0].tv_nsec = 0;
}

/* Calculates the average timespec of a timespec array. Returns the result via
 * 'res' argument. 
*/ 
static void average_timespec_array(struct timespec* tsa, unsigned int n, struct timespec* res){
    time_t sum_tv_sec = 0;
    long sum_tv_nsec = 0;
    for(int i = 0; i < n; i++){
        sum_tv_sec += tsa[i].tv_sec;
        sum_tv_nsec += tsa[i].tv_nsec;
    }
    res->tv_sec = (time_t)((double)sum_tv_sec / (double)n);
    res->tv_nsec = (long)((double)sum_tv_nsec / (double)n);
}

/* Converts a time stored in a timespec struct to its equivilent value, in 
 * seconds, stored as a double.
*/
static double timespec_to_double(struct timespec* ts){
    return (double)ts->tv_sec + ((double)ts->tv_nsec / 1000000000.0);
}

//==============================================================================
// Public Functions
//==============================================================================

/* Stores all data needed to manage gameloop time (control frame rate, calculate
 * integration period dt etc).
 * 
 * <param isGoverning>
 *   Flag to set frame rate governing on/off. When on, if the current loop takes
 *   less time to execute that dt_t, the process will sleep for the remaining 
 *   time. If off, will not sleep, instead the next iteration is started 
 *   immedietly.
 * </param>
 * <param fps>
 *   The current frame rate of the application.
 * </param>
 * <param dt_lim>
 *   The max value which dt can have; protects against large frame spikes by 
 *   capping the dt that can be returned to the caller. Remember dt is used as
 *   the integration period in the gameloop hence large values of dt create 
 *   unstable updates. 
 * 
 *   Note, if real execution time is larger than this value then it will be 
 *   impossible for the app to maintain time sync with real time; the game 
 *   will run slow. However it will be more stable.
 * 
 *   Why? Remember, dt is the prediction for the time it will take to update the 
 *   next iteration of the game loop, if the prediction is accurate then 
 *   integrating over it in the loop will keep the game time and real time in sync.
 *   By setting an upper limit to our prediction it means it prevents our game
 *   keeping up with real time if the real time it takes to process the loop 
 *   exceeds the upper limit. Importantly the cap is not reflected in the FPS
 *   value. The fps reflects the real rate at which the app is updating.
 * 
 *   Note: by default the limit is set to twice the governed frame rate if 
 *   governing is used, or 100000000ns == 10FPS if not governing.   
 * </param>
 * <param dt>
 *   The estimate for how long it will take to execute the current loop 
 *   iteration.
 * </param>
 * <param dt_t>
 *   If frame rate governing is on, represents the target execution period. This
 *   value sets the max frame rate.
 * </param>
 * <param dt_s>
 *   Time spent sleeping during the previously exected frame.
 * </param>
 * <param dt_r_his>
 *   The history of real time loop iteration measurements; how long it took to
 *   execute the previous DT_HIS_CNT frames. Used to calculate dt, which is
 *   taken as the average over this history.
 * </param>
 * <param t_r[2]>
 *   Measurements (start, [0], and end, [1]) of real/calander time in the last 
 *   frame executed. Includes any time the process spent sleeping.
 * </param>
 * <param t_e[2]>
 *   Measurements (start, [0], and end, [1]) of process time in the last frame 
 *   executed. Does NOT include time the process spent sleeping; used to 
 *   calculate sleep duration.
 * </param>
*/
typedef struct _looptimedata LoopTimeData;

/* Must call at start of each frame. Measures the time at which the frame 
 * started.
*/
void start_frame(LoopTimeData* p_ltd){
    clock_gettime(CLOCK_REALTIME, &p_ltd->t_r[0]);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &p_ltd->t_e[0]);
}

/* Must call at end of each frame. Measures the time at which the frame 
 * ended and updates the LoopTimeData accordingly. If frame governing is on, 
 * also sleeps the process.
*/
void end_frame(LoopTimeData* p_ltd){
    /*measure 2nd execution time and calculate execution period...*/
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &p_ltd->t_e[1]);
    struct timespec dt_e;
    diff_t(&p_ltd->t_e[0], &p_ltd->t_e[1], &dt_e);
    
    /*If we are governing frame rate and the execution time is less than
     *the target time, then sleep for the remainder.*/
    p_ltd->dt_s.tv_sec = p_ltd->dt_s.tv_nsec = 0;
    double dt_s_sec = 0.0;
    if(p_ltd->is_governing){
        dt_s_sec = diff_elapsed_s(&dt_e, &p_ltd->dt_t);
        if(dt_s_sec > 0){
            diff_t(&dt_e, &p_ltd->dt_t, &p_ltd->dt_s);
            sleep_interval(&p_ltd->dt_s);
        }
    }
    
    /*take 2nd real time measurement and calculate the period...*/
    struct timespec dt_r;
    clock_gettime(CLOCK_REALTIME, &p_ltd->t_r[1]);/*should reflect sleep time*/
    diff_t(&p_ltd->t_r[0], &p_ltd->t_r[1], &dt_r);
    
    /*update measurement histories...*/
    shift_timespec_array(p_ltd->dt_r_his, DT_HIS_CNT);
    p_ltd->dt_r_his[0].tv_sec = dt_r.tv_sec; 
    p_ltd->dt_r_his[0].tv_nsec = dt_r.tv_nsec;
    
    /*update dt prediction...*/
    average_timespec_array(p_ltd->dt_r_his, DT_HIS_CNT, &p_ltd->dt);

    /*update fps*/
    p_ltd->fps = 1.0 / timespec_to_double(&p_ltd->dt);

    /*cap dt if need exceeded limit...
     *note: this will result in the fps not reflecting the update time dt for the next loop.
     */
    double dt_le_sec = 0.0; /*dt of limited exceeded - diff between dt and dt_limit*/
    dt_le_sec = diff_elapsed_s(&p_ltd->dt, &p_ltd->dt_lim);
    if(dt_le_sec < 0){ /*exceeded limit so clamp...*/
        p_ltd->dt.tv_sec = p_ltd->dt_lim.tv_sec;
        p_ltd->dt.tv_nsec = p_ltd->dt_lim.tv_nsec;
    }
}

/* Must be called before any other module function to setup the loop data object.
 */
int init_loop_data(LoopTimeData* p_ltd){
    if(p_ltd == NULL)
        return 1;
    p_ltd->is_governing = false;
    p_ltd->fps = 0.0;
    p_ltd->dt_lim.tv_sec = 0; p_ltd->dt_lim.tv_nsec = 100000000; /*max dt of 100ms == 10FPS*/
    p_ltd->dt.tv_sec = p_ltd->dt.tv_nsec = 0;
    p_ltd->dt_t.tv_sec = 0; p_ltd->dt_t.tv_nsec = 0;
    zero_timespec_array(p_ltd->dt_r_his, DT_HIS_CNT);
    return 0;
}

/* Enable frame rate governing.
 *
 * <note>
 *   In governing mode the system attempts to fix the frame rate at a given
 *   value. If the game runs faster, the thread will sleep to make up the time, if 
 *   it runs slower it will not sleep to attempt to catch up lost time.
 * </note>
 * <param target_ns>
 *   The target execution period for each iteration of the game loop in nanoseconds.
 *   note: 16000000ns === 60FPS, 32000000 === 30FPS.
 * </param>
 */
int enable_governing(LoopTimeData* p_ltd, long target_ns){
    if(p_ltd == NULL)
        return 1;
    p_ltd->is_governing = true;
    p_ltd->dt_t.tv_sec = 0; p_ltd->dt_t.tv_nsec = target_ns;
    p_ltd->dt_lim.tv_nsec = (2 * p_ltd->dt_t.tv_nsec); /*max dt of twice target, half target FPS*/
    return 0;
}

/* Disables governing mode. In non-governing mode the system will not sleep to cap the
 * frame rate, rather it will run as fast as possible and simply measure the fps.
 */
int disable_governing(LoopTimeData* p_ltd){
    if(p_ltd == NULL)
        return 1;
    p_ltd->dt_lim.tv_nsec = 100000000; /*max dt of 100ms == 10FPS*/
    p_ltd->is_governing = false;
    return 0;
}

/* Extracts the fps from the time loop data and returns it.
 */
double get_fps(LoopTimeData* p_ltd){
    if(p_ltd == NULL)
        return 0.0;
    return p_ltd->fps;
}

/* Extracts the integration period (dt) from the loop time data and returns it
 * in seconds as a double. This is the prediction for how long it will take to
 * execute the next game loop iteration. You should integrate your gameloop over
 * this period.
 * 
 * note: the integration period is capped so it stops being an accurate prediction
 * of execution time if the real execution time exceeds the cap.
 */
double get_integration_period_s(LoopTimeData* p_ltd){
    if(p_ltd == NULL)
        return -1.0;
    return timespec_to_double(&p_ltd->dt);
}