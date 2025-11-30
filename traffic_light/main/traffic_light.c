#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#define RED_GPIO 4
#define YELLOW_GPIO 2
#define GREEN_GPIO 15

uint32_t red_time = 5000;
uint32_t yellow_time = 2000;
uint32_t green_time = 5000;

void app_main(void)
{
    gpio_reset_pin(RED_GPIO);
    gpio_reset_pin(YELLOW_GPIO);
    gpio_reset_pin(GREEN_GPIO);

    gpio_set_direction(RED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(YELLOW_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_GPIO, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(RED_GPIO, 1);
        vTaskDelay(red_time / portTICK_PERIOD_MS);

        gpio_set_level(RED_GPIO, 0);
        gpio_set_level(YELLOW_GPIO, 1);
        vTaskDelay(yellow_time / portTICK_PERIOD_MS);

        gpio_set_level(YELLOW_GPIO, 0);
        gpio_set_level(GREEN_GPIO, 1);
        vTaskDelay(green_time / portTICK_PERIOD_MS);
        gpio_set_level(GREEN_GPIO, 0);
    }
}
