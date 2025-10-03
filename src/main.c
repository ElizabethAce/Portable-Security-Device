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
/** Includes **/
#include <stdio.h>              // Provides printf()
#include "freertos/FreeRTOS.h"  // core FreeRTOS types and functions
#include "freertos/task.h"      // Allows use of non-blocking delay function, task APIs such as vTaskDelay()
#include "driver/gpio.h"        // Includes functions required to config and control GPIOs

/** Defines **/
#define GREEN_LED   GPIO_NUM_2 
#define RED_LED     GPIO_NUM_5
#define REED_SW     GPIO_NUM_38
#define BUZZER      GPIO_NUM_46
#define LOW 0
#define HIGH 1

/** Prototypes **/

void app_main(void) {
    // Reset and configure GPIO pins
    gpio_reset_pin(GREEN_LED);
    gpio_reset_pin(RED_LED);
    gpio_reset_pin(REED_SW);
    gpio_reset_pin(BUZZER);

    gpio_set_direction(GREEN_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(RED_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUZZER, GPIO_MODE_OUTPUT);

    // Configure reed switch as input
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << REED_SW),    // Select GPIO4 (bitmask)
        .mode = GPIO_MODE_INPUT,              // Set pin mode to INPUT
        .pull_up_en = GPIO_PULLUP_ENABLE,     // Enable pull-up resistor
        .pull_down_en = GPIO_PULLDOWN_DISABLE,// Disable pull-down resistor
        .intr_type = GPIO_INTR_DISABLE        // No interrupts for now
    };
    gpio_config(&io_conf);

    // Initialize state
    gpio_set_level(RED_LED, LOW);
    gpio_set_level(BUZZER, LOW);
    gpio_set_level(GREEN_LED , HIGH);      // Turn on green LED
    
    vTaskDelay(pdMS_TO_TICKS(500));

    while (1) {
        uint8_t sw_reading = gpio_get_level(REED_SW);
        printf("Reading 1: %d\n", sw_reading);

        if (sw_reading == HIGH) {
            printf("Reading 2: %d\n", sw_reading);
            printf("OPEN DETECTED\n");
            gpio_set_level(GREEN_LED, LOW);
            // FLASH RED LEDS 
            gpio_set_level(RED_LED, HIGH);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(RED_LED, LOW);
            vTaskDelay(pdMS_TO_TICKS(500));
            
            // Sound Buzzer
            gpio_set_level(BUZZER, HIGH);
            vTaskDelay(pdMS_TO_TICKS(.20));
            gpio_set_level(BUZZER, LOW);
            vTaskDelay(pdMS_TO_TICKS(.20));
        }
        else {
            printf("Open NOT detected\n");
            printf("Reading 3: %d\n", sw_reading);
            gpio_set_level(RED_LED, LOW);
            gpio_set_level(GREEN_LED, HIGH);
            gpio_set_level(BUZZER, LOW);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}
