#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/ledc.h"
#include "hal/ledc_types.h"
#include "driver/gpio.h"
#include "soc/gpio_reg.h"

uint32_t delay = 2000;
uint32_t shine_period = 500;

void app_main(void)
{
    printf("Hello monkeys!\n");

    /* Monkey way */
    gpio_reset_pin(2);
    gpio_set_direction(2, GPIO_MODE_OUTPUT);

    while(1)
    {
        vTaskDelay(delay / portTICK_PERIOD_MS);

        gpio_set_level(2, 1);

        vTaskDelay(shine_period / portTICK_PERIOD_MS);
    
        gpio_set_level(2, 0);
    }
}
