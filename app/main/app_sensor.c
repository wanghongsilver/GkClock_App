#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#include "esp_log.h"

#include "app_sensor.h"

static const char *SENSORTAG = "app_sensor";
static QueueHandle_t sensor_QueueHandle_t = NULL;
static int sensor_timer_cnt=0;

static void sensor_timer_callback(TimerHandle_t xTimer)
{
    struct SensorEvent test;

    if(sensor_timer_cnt++ > (SENSOR_TRIGGER_MAX_TICKS/SENSOR_TRIGGER_MIN_TICKS))
    {
        sensor_timer_cnt = 0;
    }

    /*chenck temp sensor*/
    if(sensor_timer_cnt % (SENSOR_TRIGGER_TEMP_TICKS/SENSOR_TRIGGER_MIN_TICKS) == 0)
    {
        test.sensor_id = sensor_timer_cnt;
        xQueueSend(sensor_QueueHandle_t,&test,0);
        test.sensor_id = 1;
        xQueueSend(sensor_QueueHandle_t,&test,0);
    }
}

static void sensor_task(void* pvParameters)
{
    struct SensorEvent test;
    while (1)
    {
        /* read sensor read event queue */
        xQueueReceive(sensor_QueueHandle_t,&test,portMAX_DELAY);
        ESP_LOGI(SENSORTAG, "sensor id: %d", test.sensor_id);
    }
    
    vTaskDelete(NULL);
}

void sensor_task_init()
{
    int err=0;
    /*create sensor read event queue*/
    sensor_QueueHandle_t = xQueueCreate(SENSOR_QUEUE_LEN, sizeof(struct SensorEvent));
    if(!sensor_QueueHandle_t)
    {
        ESP_LOGE(SENSORTAG, "create sensor queue fail!");
        return;
    }

    /*create soft timer to trigger sensor read event*/
    TimerHandle_t  sensor_TimerHandle_t = NULL;
    sensor_TimerHandle_t = xTimerCreate("SensorTimer",
                                        SENSOR_TRIGGER_MIN_TICKS,
                                        pdTRUE,
                                        NULL,
                                        &sensor_timer_callback);
    if(!sensor_TimerHandle_t)
    {
        ESP_LOGE(SENSORTAG, "create sensor timer fail!");
        return;
    }

    xTimerStart(sensor_TimerHandle_t,SENSOR_TRIGGER_MIN_TICKS);

    /*create sensor task to read sensor*/
    err = xTaskCreate(&sensor_task, 
                    "sensor_task", 
                    2048, 
                    NULL, 
                    10, 
                    NULL);
    ESP_LOGI(SENSORTAG, "sensor task init: %d", err);
}