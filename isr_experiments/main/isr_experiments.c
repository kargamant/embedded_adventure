#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/ledc.h"
#include "driver/timer.h"
#include "hal/ledc_types.h"
#include "driver/gpio.h"
#include "soc/gpio_reg.h"
#include "esp_intr_types.h"
#include "soc/timer_group_struct.h"

uint32_t delay = 2000000;
uint32_t shine_period = 500000;

void led_handler(void* arg)
{
    static volatile uint8_t state = 0;

    timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_0);
    //printf("intr status was cleared\n");
    timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_0);

    state = ~state;
    state &= 0x01;
    gpio_set_level(2, state);
    // printf("yellow turned: %d\n", state);

    // TIMERG0.int_clr_timers.t0 = 1;
}

void app_main(void)
{
    printf("Hello monkeys!\n");

    // timer setup
    timer_config_t timer_config = {
        .alarm_en = true,
        .counter_en = false,
        .counter_dir = 1,
        .auto_reload = true,
        .divider = 80
    };

    timer_init(TIMER_GROUP_0, TIMER_0, &timer_config);

    printf("timer initted\n");

    timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, delay);

    printf("alarm value set\n");

    timer_enable_intr(TIMER_GROUP_0, TIMER_0);

    printf("timer interrupt enabled\n");

    timer_isr_register(TIMER_GROUP_0, TIMER_0, &led_handler, NULL, ESP_INTR_FLAG_LEVEL1, NULL);

    printf("isr registered\n");

    // gpio setup
    gpio_reset_pin(2);
    gpio_set_direction(2, GPIO_MODE_OUTPUT);

    timer_start(TIMER_GROUP_0, TIMER_0);

    // printf("timer started\n");

    // timer_deinit(TIMER_GROUP_0, TIMER_0);
}
