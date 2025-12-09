#include "utils.h"

#define RED_GPIO 4
#define YELLOW_GPIO 2
#define GREEN_GPIO 15


esp_err_t red_uri_handler(httpd_req_t* req)
{
    static uint8_t state = 0;
    state &= 0x1;
    gpio_set_level(RED_GPIO, ~state);
    printf("red turned: %d\n", ~state);
    state = (~state) & 0x1;

    return ESP_OK;
}

esp_err_t yellow_uri_handler(httpd_req_t* req)
{
    static uint8_t state = 0;
    state &= 0x1;
    gpio_set_level(YELLOW_GPIO, ~state);
    printf("yellow turned: %d\n", ~state);
    state = (~state) & 0x1;

    return ESP_OK;
}

esp_err_t green_uri_handler(httpd_req_t* req)
{
    static uint8_t state = 0;
    state &= 0x1;
    gpio_set_level(GREEN_GPIO, ~state);
    printf("greeb turned: %d\n", ~state);
    state = (~state) & 0x1;

    return ESP_OK;
}
esp_err_t stop_uri_handler(httpd_req_t* req)
{
    httpd_stop(*((httpd_handle_t*)req->user_ctx));
    wifi_off();

    return ESP_OK;
}

void app_main(void)
{

    gpio_reset_pin(RED_GPIO);
    gpio_reset_pin(YELLOW_GPIO);
    gpio_reset_pin(GREEN_GPIO);

    gpio_set_direction(RED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(YELLOW_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_GPIO, GPIO_MODE_OUTPUT);

    netif_setup();

    connect_to_wifi("Sunshine", "140009Pobratimov2275");

    httpd_handle_t server_handle = NULL;
    httpd_config_t http_config = HTTPD_DEFAULT_CONFIG();
    
    if(httpd_start(&server_handle, &http_config) == ESP_OK)
    {
        // register stuff
        httpd_uri_t red_uri = {
            .uri = "/red",
            .method = HTTP_GET,
            .handler = &red_uri_handler
        };
        httpd_uri_t yellow_uri = {
            .uri = "/yellow",
            .method = HTTP_GET,
            .handler = &yellow_uri_handler
        };
        httpd_uri_t green_uri = {
            .uri = "/green",
            .method = HTTP_GET,
            .handler = &green_uri_handler
        };
        httpd_uri_t stop_uri = {
            .uri = "/stop",
            .method = HTTP_GET,
            .handler = &stop_uri_handler,
            .user_ctx = &server_handle
        };

        httpd_register_uri_handler(server_handle, &red_uri);
        httpd_register_uri_handler(server_handle, &yellow_uri);
        httpd_register_uri_handler(server_handle, &green_uri);
        httpd_register_uri_handler(server_handle, &stop_uri);
    }
    printf("http server started\n");

    while(1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
