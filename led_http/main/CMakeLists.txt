idf_component_register(SRCS "led_http.c"
                    REQUIRES esp_wifi nvs_flash esp_http_client esp_driver_gpio esp_http_server
                    INCLUDE_DIRS ".")
