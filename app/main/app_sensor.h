#ifndef __APP_SENSOR_H
#define __APP_SENSOR_H

#define SENSOR_TRIGGER_MAX_TICKS (1000) 
#define SENSOR_TRIGGER_200ms_TICKS (200) 
#define SENSOR_TRIGGER_MIN_TICKS (10) 
#define SENSOR_TRIGGER_TIMER_ID  (1)
#define SENSOR_QUEUE_LEN         (10)

enum{
    SENSOR_ID_VOLT=0,
    SENSOR_ID_TEMP,
};

struct SensorEvent{
    int sensor_id;
};


void sensor_task_init();

#endif