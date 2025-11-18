## Version 0.1.6 - BLE Version 1
- Restrategizing BLE by using Arduino and ESPIDF
- First draft ready to be tested with an existing app like LightBlue
- Commented main.c out to remove potential conflicts with .cpp

## Version 0.1.5 - Clean-up
- Clean-up and possible hybrid change

## Version 0.1.4
- .ini platform change to newer version to force an update

## Version 0.1.3
- Linker issue:
    - Ran pio run -t menuconfig
    - Component config → Bluetooth → [Enable Bluetooth]
    - Finally reached a compile error than just missing-libraries noise


## Version 0.1.2
- Issues:
    - Linker & pio command issues
    - To fix command not found issue:
    export PATH=$PATH:~/.platformio/penv/bin
    pio run -t clean
    echo 'export PATH=$PATH:~/.platformio/penv/bin' >> ~/.zshrc
- link_ble.py added for linker issues
- Linker issues unresolved
- Update push

## Version 0.1.1
- Bluetooth Server in progress

- Missing header file bt_controller_config.h — it wasn’t found in the installed ESP-IDF framework so BT_CONTROLLER_INIT_CONFIG_DEFAULT() macro couldn't be used.
    - Manually defined a configuration struct to work around issue
- Issues w/ BLE Headers
    - Manually searched for them and included them into .ini file to get rid of squiggles under #includes in BLE_server.c 
- Still needs further modification
    - Will add error checks and print statements for future testing

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
    