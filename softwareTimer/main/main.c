#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"    
#include "freertos/timers.h"

#define CONFIG_FREERTOS_HZ 100

static TimerHandle_t xTimer = NULL;
static const char *TAG = "Message";   

// Timer callback function
void vTimerCallback(TimerHandle_t xTimer){
    
    ESP_LOGI(TAG, "Timer %d Expired \n", (int)pvTimerGetTimerID(xTimer));     
   
}

void app_main(void)
{
    // Create a timer with a 2-second period
    xTimer = xTimerCreate("Timer 0", 2000/portTICK_PERIOD_MS, pdTRUE, (void *)0, vTimerCallback);
    assert(xTimer != NULL);
    
    // Start the timer
    xTimerStart(xTimer, portMAX_DELAY);
}
