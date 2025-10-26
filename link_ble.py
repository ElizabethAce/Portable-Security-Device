# link_ble.py
# PlatformIO passes the SCons environment to this script.
# This script will request the bt / nvs_flash / esp_system / esp_event / esp_timer libs
# be linked in. This is a fragile workaround compared to real components, but it works.

Import("env")

# Make sure this runs only when building (not when running other tasks)
if env.GetProjectOption("board"):
    # Request link to IDF components by name (these are the library basenames that the IDF creates)
    env.Append(LIBS=[
        "bt",
        "nvs_flash",
        "esp_system",
        "esp_event",
        "esp_timer"
    ])

    # Also ensure include paths are available for IntelliSense and compile
    env.Append(CPPPATH=[
        "/Users/elizabethacevedo/.platformio/packages/framework-espidf/components/bt/include",
        "/Users/elizabethacevedo/.platformio/packages/framework-espidf/components/bt/include/esp32/include",
        "/Users/elizabethacevedo/.platformio/packages/framework-espidf/components/bt/host/bluedroid/api/include",
        "/Users/elizabethacevedo/.platformio/packages/framework-espidf/components/bt/common/api",
        "/Users/elizabethacevedo/.platformio/packages/framework-espidf/components/bt/controller/esp32s3/include"
    ])