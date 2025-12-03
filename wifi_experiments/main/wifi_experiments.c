#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"

void app_main(void)
{
    printf("Hello, monkeys!\n\n");

    nvs_flash_init();

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    printf("some default things\n");

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&config);
    printf("wifi driver initted!\n");

    esp_wifi_set_mode(WIFI_MODE_STA);
    printf("wifi station mode set!\n");

    esp_wifi_start();
    printf("wifi service started!\n");

    esp_wifi_scan_start(NULL, true);
    printf("wifi scan started!\n");

    // retrievement
    uint16_t ap_number = 10;
    wifi_ap_record_t ap_records[10];
    esp_wifi_scan_get_ap_records(&ap_number, ap_records);

    for(int i=0; i<ap_number; i++)
    {
        wifi_ap_record_t ap = ap_records[i];
        printf("wifi_name: %s\n", (const char*)ap.ssid);
        printf("mac address: %x:%x:%x:%x:%x:%x\n", ap.bssid[0], ap.bssid[1], ap.bssid[2], ap.bssid[3], ap.bssid[4], ap.bssid[5]);
    }

    // connect

    // wifi_interface_t mode = WIFI_IF_STA;
    // unsigned char network_name[32] = "Sunshine";
    // unsigned char password[64] = "140009Pobratimov2275"; 
    // wifi_sta_config_t configuration;
    // configuration.ssid = (uint8_t[32]){'S', 'u', 'n', 's', 'h', 'i', 'n', 'e'};
    // configuration.password = password;
    // esp_wifi_set_config(mode, &configuration);
    
    // esp_err_t err_code = esp_wifi_connect();

    // if(err_code == ESP_OK)
    //     printf("successssssssssssssssssss\n");
    // else
    //     printf("couldn't connect sorry bro\n");


    // stopping point
    esp_wifi_stop();
    printf("wifi service stopped!\n");

    esp_wifi_deinit();
    printf("wifi driver deinitted!\n");
}
