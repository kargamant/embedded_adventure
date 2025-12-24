#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "freertos/task.h"

void monkey_task(void* params)
{
    while(1)
    {
        printf("monkey_name: %s\n", (char*)params);
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}

void donkey_task(void* params)
{
    while(1)
    {
        printf("donkey_name: %s\n", (char*)params);
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    printf("Hello, monkeys!\n\n");
    static char params[8] = "embedded";
    TaskHandle_t m_task_handle = NULL;
    TaskHandle_t d_task_handle = NULL;

    // rtos create task
    xTaskCreate(monkey_task, "monkey_name", 1024, params, tskIDLE_PRIORITY + 1, &m_task_handle);
    xTaskCreate(donkey_task, "donkey_name", 1024, params, tskIDLE_PRIORITY + 1, &d_task_handle);
    printf("tasks was succesfully created!\n\n");

    params[0] = 'g';

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    if(m_task_handle)
    {
        vTaskDelete(m_task_handle);
    }

    if(d_task_handle)
    {
        vTaskDelete(d_task_handle);
    }
}
