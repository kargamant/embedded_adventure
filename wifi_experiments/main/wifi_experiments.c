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
    uint16_t ap_number = 12;
    wifi_ap_record_t ap_records[12];
    esp_wifi_scan_get_ap_records(&ap_number, ap_records);

    for(int i=0; i<ap_number; i++)
    {
        wifi_ap_record_t ap = ap_records[i];
        printf("wifi_name: %s\n", (const char*)ap.ssid);
        printf("mac address: %x:%x:%x:%x:%x:%x\n", ap.bssid[0], ap.bssid[1], ap.bssid[2], ap.bssid[3], ap.bssid[4], ap.bssid[5]);
    }

    // connect

    wifi_interface_t mode = WIFI_IF_STA;
    unsigned char network_name[32] = "abcdefg";
    unsigned char password[64] = "abcdefg"; 
    wifi_sta_config_t sta_configuration;
    
    for(int i=0; i<17; i++)
    {
        sta_configuration.ssid[i] = network_name[i];
    }
    
    for(int i=0; i<12; i++)
    {
        sta_configuration.password[i] = password[i]; 
    }

    sta_configuration.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;

    wifi_config_t configuration;
    configuration.sta = sta_configuration;
    esp_wifi_set_config(mode, &configuration);
    
    esp_err_t err_code = esp_wifi_connect();

    if(err_code == ESP_OK)
        printf("successssssssssssssssssss\n");
    else
        printf("couldn't connect sorry bro\n");

    vTaskDelay(20000 / portTICK_PERIOD_MS);

    // stopping point
    esp_wifi_stop();
    printf("wifi service stopped!\n");

    esp_wifi_deinit();
    printf("wifi driver deinitted!\n");
}
