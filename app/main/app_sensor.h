#ifndef __APP_SENSOR_H
#define __APP_SENSOR_H

#define SENSOR_TRIGGER_MAX_TICKS (1000) 
#define SENSOR_TRIGGER_TEMP_TICKS (200) 
#define SENSOR_TRIGGER_MIN_TICKS (10) 
#define SENSOR_TRIGGER_TIMER_ID  (1)
#define SENSOR_QUEUE_LEN         (10)

struct SensorEvent{
    int sensor_id;
};


void sensor_task_init();

#endif