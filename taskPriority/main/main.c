// This code creates two FreeRTOS tasks on an ESP32:

//     task1 (priority 2): Logs "Task 1 is running" every 20 ms, then yields using vTaskDelay.
//     task2 (priority 1): Continuously logs "Task 2 is running" without delay.

// task1 will preempt task2 due to its higher priority. task2 runs when task1 is in a blocked state (during the 20 ms delay).
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "driver/gpio.h"
    #include "esp_log.h"

    static const char *TAG = "Task";

    void task1(void *pvParameters)
    {
        while(1)
        {
            ESP_LOGI(TAG, "Task 1 is running");
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }

    void task2(void *pvParameters)
    {
        while(1)
        {
            ESP_LOGI(TAG, "Task 2 is running");
        }

    }

    void app_main(void)
    {
        BaseType_t xRetValTask1 = xTaskCreate(task1, "task1", 2048, NULL, 2, NULL);
        BaseType_t xRetValTask2 = xTaskCreate(task2, "task2", 2048, NULL, 1, NULL);
        assert(xRetValTask1 == pdPASS);
        assert(xRetValTask2 == pdPASS);

    }