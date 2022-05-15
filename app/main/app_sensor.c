#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#include "esp_log.h"
#include "driver/adc.h"

#include "app_sensor.h"

static const char *SENSORTAG = "app_sensor";
static QueueHandle_t sensor_QueueHandle_t = NULL;
static int sensor_timer_cnt=0;

static void bsp_volt_init(void)
{
    // 1. init adc
    adc_config_t adc_config;

    // Depend on menuconfig->Component config->PHY->vdd33_const value
    // When measuring system voltage(ADC_READ_VDD_MODE), vdd33_const must be set to 255.
    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 8; // ADC sample collection clock = 80MHz/clk_div = 10MHz
    ESP_ERROR_CHECK(adc_init(&adc_config));
}

static void read_volt(void)
{
    uint16_t adc_data[10];
    if (ESP_OK == adc_read_fast(adc_data, 10)) {
        ESP_LOGI(SENSORTAG, "volt: %d", (adc_data[0]+adc_data[9])/2);
    }
    else
    {
        ESP_LOGE(SENSORTAG, "read volt fail");
    }
}

static void sensor_timer_callback(TimerHandle_t xTimer)
{
    struct SensorEvent test;

    if(sensor_timer_cnt++ > (SENSOR_TRIGGER_MAX_TICKS/SENSOR_TRIGGER_MIN_TICKS))
    {
        sensor_timer_cnt = 0;
    }

    /*chenck temp sensor*/
    if(sensor_timer_cnt % (SENSOR_TRIGGER_200ms_TICKS/SENSOR_TRIGGER_MIN_TICKS) == 0)
    {
        test.sensor_id = SENSOR_ID_VOLT;
        xQueueSend(sensor_QueueHandle_t,&test,0);
        test.sensor_id = SENSOR_ID_TEMP;
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
        if(test.sensor_id == SENSOR_ID_VOLT)
        {
            read_volt();
        }
    }
    
    vTaskDelete(NULL);
}

void sensor_task_init()
{
    int err=0;
    /*sensor bsp init*/
    bsp_volt_init();


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