#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h" // Include the correct header file
#include "esp_log.h"    

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

static const char *TAG = "main";
static int count = 0;

SemaphoreHandle_t xSemaphore;

void task1(void *pvParemteres)
{
    while(1)
    {
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            count++;
            ESP_LOGI(TAG, "Task 1: Semaphore taken");
            ESP_LOGI(TAG, "Task 1: Count = %d", count);
            xSemaphoreGive(xSemaphore);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        }
}

void task2(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            count++;
            ESP_LOGI(TAG, "Task 2: Semaphore taken");
            ESP_LOGI(TAG, "Task 2: Count = %d", count);
            xSemaphoreGive(xSemaphore);
            vTaskDelay(200 / portTICK_PERIOD_MS);
            
        }

    }
}
    
void app_main(void)
{
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);  // Initialize semaphore
    BaseType_t xRetValTask1 = xTaskCreate(task1, "task 1", 4096, NULL, 2, &task1Handle);
    BaseType_t xRetValTaks2 = xTaskCreate(task2, "task 2", 4096, NULL, 1, &task2Handle);
    assert(xRetValTask1 == pdPASS && xRetValTaks2 == pdPASS);
}
