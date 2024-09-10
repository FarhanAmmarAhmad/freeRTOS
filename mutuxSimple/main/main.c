#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"


static int sharedResource = 0;
static const char *TAG = "TAG";

SemaphoreHandle_t xMutex;


TaskHandle_t xTask1Hanlder = NULL;
TaskHandle_t xTask2Handler = NULL;

void vTask1(void *pvParameters){
    while(1){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            sharedResource++;
            ESP_LOGI(TAG, "Task 1: %d\n", sharedResource);
            vTaskDelay(200 / portTICK_PERIOD_MS);
            xSemaphoreGive(xMutex);
        }
    }
}

void vTask2(void *pvParameters){
    while(1){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            sharedResource++;
            ESP_LOGI(TAG, "Task 2: %d\n", sharedResource);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Add delay after releasing the mutex
    }
}

void app_main(void)
{
    xMutex = xSemaphoreCreateMutex();

    if(xMutex == NULL){
        printf("Mutex creation failed\n");
        while(1);
    }

    BaseType_t xRetValTask1 = xTaskCreate(vTask1, "Task 1", 2048, (void *) "Task 1", 1, &xTask1Hanlder);    
    BaseType_t xRetValTask2 = xTaskCreate(vTask2, "Task 2", 2048, (void *) "Task 2", 2, &xTask2Handler); 
    assert(xRetValTask1 == pdPASS && xRetValTask2 == pdPASS);

}
