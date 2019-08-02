#ifndef _LOOPTIME_H_
#define _LOOPTIME_H_

/* Enforces including of interface files -> the preprocessor will replace all function 
 * names in this file and in looptime.c with the defines below. If this header is not
 * included in a src file which uses this module then the function names will be
 * unrecognised since they would of not been changed in the src file, only in looptime.h
 * and looptime.c
 * 
 * note: to use the module you should call the real function names not the defined 
 * replacements, e.g. call start_frame not looptime_start_frame. calling the latter
 * would defeat the purpose of this section.
 */ 
#define start_frame looptime_start_frame
#define end_frame looptime_end_frame
#define init_loop_data looptime_init_loop_data
#define enable_governing looptime_enable_governing
#define disable_governing looptime_disable_governing
#define get_fps looptime_get_fps
#define get_integration_period_s looptime_get_integration_period_s


#define DT_HIS_CNT 5 /*number/count of past loop durations to average over*/


/* Stores all data needed to keep track of gameloop time. To use this module you should
 * instantiate an instance of this struct for use with the module functions. However you
 * do not use this struct directly, only via the functions.
 */
typedef struct _looptimedata{
    bool is_governing;
    double fps;
    struct timespec dt_lim;
    struct timespec dt;
    struct timespec dt_t;
    struct timespec dt_s;
    struct timespec dt_r_his[DT_HIS_CNT];
    struct timespec t_r[2];
    struct timespec t_e[2];
}LTData;

/* ------------------------------------------------------------------------------------
 * Must call at start of each frame. Measures the time at which the frame 
 * started.
*/
extern void start_frame(LTData* p_ltd);

/* ------------------------------------------------------------------------------------
 * Must call at end of each frame. Measures the time at which the frame 
 * ended and updates the LoopTimeData accordingly. If frame governing is on, 
 * also sleeps the process.
*/
extern void end_frame(LTData* p_ltd);

/* ------------------------------------------------------------------------------------
 * Must be called before any other module function to setup the loop data object.
 */
extern int init_loop_data(LTData* p_ltd);

/* ------------------------------------------------------------------------------------
 * Enable frame rate governing.
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
extern int enable_governing(LTData* p_ltd, long target_ns);

/* ------------------------------------------------------------------------------------
 * Disables governing mode. In non-governing mode the system will not sleep to cap the
 * frame rate, rather it will run as fast as possible and simply measure the fps.
 */
extern int disable_governing(LTData* p_ltd);

/* ------------------------------------------------------------------------------------
 * Extracts the fps from the time loop data and returns it.
 */
extern double get_fps(LTData* p_ltd);

/* ------------------------------------------------------------------------------------
 * Extracts the integration period (dt) from the loop time data and returns it
 * in seconds as a double. This is the prediction for how long it will take to
 * execute the next game loop iteration. You should integrate your gameloop over
 * this period.
 * 
 * note: the integration period is capped so it stops being an accurate prediction
 * of execution time if the real execution time exceeds the cap.
 */
extern double get_integration_period_s(LTData* p_ltd);


#endif