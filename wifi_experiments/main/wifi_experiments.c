#include <stdio.h>
#include "esp_wifi.h"

void app_main(void)
{
    printf("Hello, monkeys!\n\n");

    // first deinit
    esp_wifi_stop();
    printf("wifi service stopped!\n");

    esp_wifi_deinit();
    printf("wifi driver deinitted!\n");


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
    uint16_t ap_number = 3;
    wifi_ap_record_t ap_records[3];
    esp_wifi_scan_get_ap_records(&ap_number, ap_records);

    for(int i=0; i<3; i++)
    {
        wifi_ap_record_t ap = ap_records[i];
        printf("wifi_name: %s\n", (const char*)ap.ssid);
        printf("mac address: %d\n", *ap.bssid);
    }



    // stopping point
    esp_wifi_stop();
    printf("wifi service stopped!\n");

    esp_wifi_deinit();
    printf("wifi driver deinitted!\n");
}
