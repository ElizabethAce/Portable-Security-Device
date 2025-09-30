/*****************************************************************************
 * File name:  main.c
 *
 * 
 * Author:    Elizabeth Acevedo
 * 
 * Date:      09/29/2025
 * 
 * Project Name: Portable Security Device
 * 
 * Description: This program detects signals from a reed switch (0 or 1) to 
 * notify user there has been a security breach with other visual and 
 * auditory features using LEDs and a buzzer.
 * 
 * 
 * Utilization: 
 *
 * 
 *****************************************************************************/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO GPIO_NUM_2 

void app_main(void) {
    // Configure the GPIO pin as output
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(200));

    while (1) {
        // Toggle LED
        gpio_set_level(BLINK_GPIO, 1);
        printf("BLINK: HIGH\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    
        gpio_set_level(BLINK_GPIO, 0);
        printf("BLINK: LOW\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}