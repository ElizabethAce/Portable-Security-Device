## Version 0.1.16 - Adding Descriptor (Include Issue)
- Issue with BLE2901 include
    - Resolved: Replaced espressif32 platform in .ini with https://github.com/pioarduino/platform-espressif32.git supporting Arduino-ESP32 3.x (Most recent version: 3.20017.241212+sha.dcc1105b  234.91MB  2024-12-12 14:33:50)
    * Checked by doing: pio pkg show framework-arduinoespressif32

## Version 0.1.15 - Adding Descriptor
- Saving Progress
- Issue with BLE2901 include

## Version 0.1.14 - Added comments to .cpp header and testing code

## Version 0.1.13 - Modifying and Testing BLE (Characteristic)
- Created a characteristic and generated UUID at https://www.uuidgenerator.net/
- Tested characteristic (Passed test)
- BLE Library issue (perhaps incompatible w/ ESP32-S3)
    - Look for alternative or rewriting code to board format
        * Resolved: Didn't need alternate library. Must've accidentally downloaded an older library that wasn't compatible with my board. So, I deleted the library from /Users/MYUSERNAME/Documents/PlatformIO/Projects/Portable-Security-Device/.pio/libdeps/esp32-s3-devkitc-1/ by doing 
        rm -rf "ESP32 BLE Arduino"
        Re-built the code and re-uploaded to board. 
        At first characteristic wasn't showing but realized I had "pService->start();" before creating the characteristic. So, I moved it after all the characteristic stuff and above starting advertising. It worked.

## Version 0.1.12 - Modifying and Testing BLE (Characteristic)
- Created a characteristic and generated UUID at https://www.uuidgenerator.net/
- Saving progress
- Issues with finding member in class, will be resolved later 
    - Resolved: Needed to create a class for characteristic
- BLE Library issue (perhaps incompatible w/ ESP32-S3)
    - Look for alternative or rewriting code to board format

## Version 0.1.11 - Modifying and Testing BLE (Characteristic)
- Creating a characteristic and generated UUID at https://www.uuidgenerator.net/
- Saving progress
- Issues with finding member in class, will be resolved later 

## Version 0.1.10 - Modifying and Testing BLE (Service)
- Created a service and generated UUID at https://www.uuidgenerator.net/
- Service UUID shows up on the app

## Version 0.1.9 - Modifying and Testing BLE (Server)
- Advertising after disconnecting
- Light LED on connect/disconnect feature (mainly for testing purposes)

## Version 0.1.8 - Testing BLE was sucessful on app
- Debugging recap:
    1. Switched from ESP-IDF to Arduino framework (just to test BLE)
	    •	Updated platformio.ini to use framework = arduino
	    •	BLE libraries resolved, #include <BLEDevice.h> stopped erroring.
    2. Serial.print does not appear → suspected USB issue
        •	Serial.println() does not show in monitor
        •	Only repeated bootloader text (“ESP-ROM…”) seen
    3. Tested both USB ports for uploads
        •	Upload failed when using the UART port → confirms UART is not used for flashing
        •	Upload succeeded when using the native USB port → correct port identified.
    4. Observed continuous boot output in the monitor
        •	Output included: rst:0x3, entry 0x403c98d0, etc.
        •	Diagnosed as “bootloader loop” only on the UART debug port, not a code crash.
            - macOS exposed both the ESP32-S3 USB interface and the UART bridge, and PlatformIO mistakenly opened the UART port instead of the USB port, which made the Serial Monitor show ROM bootloader messages instead of my actual firmware output.
    5. Removed USB/CDC flags and attempted a clean reset
        •	Removed the extra build flags that resulted to be unnecessary 
        •	Pressed BOOT once on native USB
    6. Re-ran BLE code → success
        •	Serial prints however are not yet visible
        •	BLE device name now visible on app LightBlue scan
        •	Issue must have been Serial monitor attaching to the wrong port and/or USB CDC not initializing cleanly.
    Need to resolve:
    - Serial monitor prints not showing up

## Version 0.1.7 - Testing BLE
- First iteration of testing:
    * Prints don't appear
    * Device doesn't show up on the app

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
    