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

    /* LEDC way */

    // let's configure timer
    ledc_timer_config_t t_conf = {
                            LEDC_LOW_SPEED_MODE, 
                            LEDC_TIMER_10_BIT, 
                            LEDC_TIMER_0,
                            1000,
                            LEDC_AUTO_CLK,
                            false};

    // let's configure channel
    ledc_channel_config_t ch_conf = {
        2,
        LEDC_LOW_SPEED_MODE,
        LEDC_CHANNEL_0,
        LEDC_INTR_DISABLE,
        LEDC_TIMER_0,
        512, // pwm duty can be adjusted here
        0
    };

    while(1) 
    {
        vTaskDelay(delay / portTICK_PERIOD_MS);

        t_conf.deconfigure = false;
        ledc_timer_config(&t_conf);
        ledc_channel_config(&ch_conf);

        vTaskDelay(shine_period / portTICK_PERIOD_MS);
        
        ledc_timer_pause(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0);
        ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);

        // let's deconfigure timer
        t_conf.deconfigure = true;
        ledc_timer_config(&t_conf);

    }
}
