#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void monkey_task(void* params)
{
    while(1)
    {
        printf("monkey_name: %s\n", (char*)params);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    printf("Hello, monkeys!\n\n");
    char* params = "embedded";
    TaskHandle_t task_handle = NULL;

    // rtos create task
    xTaskCreate(monkey_task, "monkey_name", 1, params, 2, &task_handle);

    if(task_handle)
    {
        vTaskDelete(task_handle);
    }
}
