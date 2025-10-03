## Version 0.1.0
- Create first version of security device that detects when the switch is opened and prints status messages
- Complete buzzer code to sound like an alarm
    • Will need to migrate buzzer from blocking software toggle to hardware PWM (LEDC) for non-blocking tone generation. (Need to research using this)
- Unexpected behaviors & mistakes I ran into: 
    • Fixed misuse of gpio_reset_pin() and gpio_set_direction() with bitwise OR (function only supports one pin at a time).
	• Resolved infinite loop caused by using while(sw_reading == HIGH) in helper function. Replaced with non-blocking main loop logic.
	• Corrected reed switch configuration (enabled proper pull-up resistor to avoid floating input).
	• Fixed inconsistent LED states (green LED not turning on in safe mode).
	• Investigated unexpected onboard RGB LED behavior; discovered RGB is picking up junk data even though I'm not using it. Ignored GPIO48 and confirmed that external breadboard LEDs functioned correctly on their assigned pins. 

## Version 0.0.1
- main.c created
- Blink LED code written in main to test ESP32 connection
- Ran into some issues: 
    • includes has squiggly lines (couldn't be found): updated board in .ini and did > Rebuild IntelliSense Index
    • LED on breadboard was not flasshing (only flashed when touched with multimeter when checking voltage): clicked reset button after reuploading changes and changed baud rate
    