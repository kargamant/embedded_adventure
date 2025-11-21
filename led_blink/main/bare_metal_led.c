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

#define GPIO_BASE_ADDR 0x3FF44000

void app_main(void)
{
    printf("Hello monkeys!\n");

    /* bare metal way */
    volatile uint32_t* gpio_func2_out_sel_cfg_reg = (volatile uint32_t*)(GPIO_BASE_ADDR + 0x530 + 0x4 * 2);
    volatile uint32_t* gpio_out_w1ts_reg = (volatile uint32_t*)(GPIO_BASE_ADDR + 0x8);
    volatile uint32_t* gpio_out_reg = (volatile uint32_t*)(GPIO_BASE_ADDR + 0x4);
    volatile uint32_t* gpio_enable_reg = (volatile uint32_t*)(GPIO_BASE_ADDR + 0x0020);
    volatile uint32_t* gpio_enable_w1ts_reg = (volatile uint32_t*)(GPIO_BASE_ADDR + 0x0024);
    volatile uint32_t* gpio_enable_w1tc_reg = (volatile uint32_t*)(GPIO_BASE_ADDR + 0x0028);
    volatile uint32_t* io_mux_gpio2_reg = (volatile uint32_t*)(0x3FF49040);

    printf("start values\n");
    printf("gpio_func2_out_sel_cfg_reg: %lx\n", *gpio_func2_out_sel_cfg_reg);
    printf("gpio_out_w1ts_reg: %lx\n", *gpio_out_w1ts_reg);
    printf("gpio_out_reg: %lx\n", *gpio_out_reg);
    printf("gpio_enable_w1ts_reg: %lx\n", *gpio_enable_w1ts_reg);
    printf("gpio_enable_reg: %lx\n", *gpio_enable_reg);
    printf("io_mux_gpio2_reg: %lx\n\n", *io_mux_gpio2_reg);


    *gpio_func2_out_sel_cfg_reg &= 0xFFFFFF00;
    *gpio_func2_out_sel_cfg_reg |= 0x00000100;

    printf("after gpio_func2_out_sel_cfg_reg setting:\n");
    printf("gpio_func2_out_sel_cfg_reg: %lx\n", *gpio_func2_out_sel_cfg_reg);
    printf("gpio_out_w1ts_reg: %lx\n", *gpio_out_w1ts_reg);
    printf("gpio_out_reg: %lx\n", *gpio_out_reg);
    printf("gpio_enable_w1ts_reg: %lx\n", *gpio_enable_w1ts_reg);
    printf("gpio_enable_reg: %lx\n", *gpio_enable_reg);
    printf("io_mux_gpio2_reg: %lx\n\n", *io_mux_gpio2_reg);

    
    *gpio_out_w1ts_reg |= (1 << 2);
    // but actually we can also do it directly
    // *gpio_out_reg |= (1 << 2); 

    printf("after gpio_out_w1ts_reg setting:\n");
    printf("gpio_func2_out_sel_cfg_reg: %lx\n", *gpio_func2_out_sel_cfg_reg);
    printf("gpio_out_w1ts_reg: %lx\n", *gpio_out_w1ts_reg);
    printf("gpio_out_reg: %lx\n", *gpio_out_reg);
    printf("gpio_enable_w1ts_reg: %lx\n", *gpio_enable_w1ts_reg);
    printf("gpio_enable_reg: %lx\n", *gpio_enable_reg);
    printf("io_mux_gpio2_reg: %lx\n\n", *io_mux_gpio2_reg);
    
    *gpio_enable_w1ts_reg |= (1 << 2);
    // but actually we can also do it directly
    // *gpio_enable_reg |= (1 << 2); 

    printf("after gpio_enable_w1ts_reg setting:\n");
    printf("gpio_func2_out_sel_cfg_reg: %lx\n", *gpio_func2_out_sel_cfg_reg);
    printf("gpio_out_w1ts_reg: %lx\n", *gpio_out_w1ts_reg);
    printf("gpio_out_reg: %lx\n", *gpio_out_reg);
    printf("gpio_enable_w1ts_reg: %lx\n", *gpio_enable_w1ts_reg);
    printf("gpio_enable_reg: %lx\n", *gpio_enable_reg);
    printf("io_mux_gpio2_reg: %lx\n\n", *io_mux_gpio2_reg);

    // doesn't really effect anything
    // *io_mux_gpio2_reg |= (1 << 13);

    // printf("after io_mux_gpio2_reg setting:\n");
    // printf("gpio_func2_out_sel_cfg_reg: %lx\n", *gpio_func2_out_sel_cfg_reg);
    // printf("gpio_out_w1ts_reg: %lx\n", *gpio_out_w1ts_reg);
    // printf("gpio_out_reg: %lx\n", *gpio_out_reg);
    // printf("gpio_enable_w1ts_reg: %lx\n", *gpio_enable_w1ts_reg);
    // printf("gpio_enable_reg: %lx\n", *gpio_enable_reg);
    // printf("io_mux_gpio2_reg: %lx\n\n", *io_mux_gpio2_reg);

    while(1)
    {
        vTaskDelay(delay / portTICK_PERIOD_MS);
        *gpio_enable_w1ts_reg |= (1 << 2);
        vTaskDelay(shine_period / portTICK_PERIOD_MS);
        *gpio_enable_w1tc_reg |= (1 << 2);
    }
}
