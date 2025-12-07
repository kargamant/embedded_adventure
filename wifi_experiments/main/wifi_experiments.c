#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include <string.h>

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        wifi_event_sta_disconnected_t* disconn =
            (wifi_event_sta_disconnected_t*)event_data;

        printf("Disconnected, reason: %d\n", disconn->reason);
        printf("ssid:\n");
        for(int i=0; i<disconn->ssid_len; i++)
        {
            printf("%c", disconn->ssid[i]);
        }
        printf("\n");
        printf("mac address: %x:%x:%x:%x:%x:%x\n", disconn->bssid[0], disconn->bssid[1], disconn->bssid[2], disconn->bssid[3], disconn->bssid[4], disconn->bssid[5]);

        if (disconn->reason == WIFI_REASON_AUTH_FAIL ||
            disconn->reason == WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT) {
            printf("❌ Wrong password!\n");
        }
    }

    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        printf("🎉 Connected and got IP!\n");
    }
}


void app_main(void)
{
    printf("Hello, monkeys!\n\n");

    // initting NVS flash
    esp_err_t nvs_err = nvs_flash_init();
    if(nvs_err == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        nvs_flash_erase();
        nvs_flash_init();
    }

    // initing network interface of esp32
    esp_netif_init();

    // event loop and handler instantiation
    esp_event_loop_create_default();

    // creating wifi station in wifi driver
    esp_netif_create_default_wifi_sta();

    // default config
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&config);
    printf("wifi driver initted!\n");

    esp_event_handler_instance_t wifi_event_handler_instance;
    esp_event_handler_instance_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            &wifi_event_handler,
            NULL,
            &wifi_event_handler_instance
    );

    esp_event_handler_instance_t ip_event_handler_instance;
    esp_event_handler_instance_register(
            IP_EVENT,
            ESP_EVENT_ANY_ID,
            &wifi_event_handler,
            NULL,
            &ip_event_handler_instance
    );

    wifi_interface_t mode = WIFI_IF_STA;
    wifi_config_t configuration = 
    {
        .sta = 
        {
            .ssid = "abcdefghijklmnop",
            .password = "abcdefghijklmnop",
            .threshold.authmode = WIFI_AUTH_WPA2_PSK
        }
    };

    // configuration.sta.sae_pwe_h2e = WPA3_SAE_PWE_BOTH;
    
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(mode, &configuration);



    // esp_wifi_scan_start(NULL, true);
    // printf("wifi scan started!\n");

    // // retrievement
    // uint16_t ap_number = 12;
    // wifi_ap_record_t ap_records[12];
    // esp_wifi_scan_get_ap_records(&ap_number, ap_records);

    // for(int i=0; i<ap_number; i++)
    // {
    //     wifi_ap_record_t ap = ap_records[i];
    //     printf("wifi_name: %s\n", (const char*)ap.ssid);
    //     printf("mac address: %x:%x:%x:%x:%x:%x\n", ap.bssid[0], ap.bssid[1], ap.bssid[2], ap.bssid[3], ap.bssid[4], ap.bssid[5]);
    // }

    // connect    
    esp_wifi_start();
    printf("wifi service started!\n");

    esp_err_t err_code = esp_wifi_connect();

    // if(err_code == ESP_OK)
    //     printf("successssssssssssssssssss\n");
    // else
    //     printf("couldn't connect sorry bro\n");

    vTaskDelay(20000 / portTICK_PERIOD_MS);

    // stopping point
    esp_wifi_stop();
    printf("wifi service stopped!\n");

    esp_wifi_deinit();
    printf("wifi driver deinitted!\n");
}
