#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define LED_GPIO 2
//typedef int BaseType_t;
//#define pdPASS ((BaseType_t)1)
//#define pdFAIL ((BaseType_t)0)
#define stack_size 1024


TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;


void blinkTask1(void *pvParameters)
{
    char *pcTaskName;
    pcTaskName = (char *)pvParameters;
    

    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    
    
    while (true)
    {
        printf("%s\n", pcTaskName);
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void blinkTask2(void *pvParameters)
{
    char *pcTaskName;
    pcTaskName = (char *)pvParameters;

    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (true)
    {
        printf("%s\n", pcTaskName);
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    BaseType_t retValTask1 = xTaskCreate(blinkTask1, "Task 1", stack_size, (void *)"Task 1 is running", 1, &task1Handle);
    BaseType_t retValTask2 = xTaskCreate(blinkTask2, "Task 2", stack_size, (void *)"Task 2 is running", 1, &task2Handle);
    assert(retValTask1 == pdPASS);
    assert(retValTask2 == pdPASS);
    
}
