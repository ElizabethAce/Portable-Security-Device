/*****************************************************************************
 * File name:  BLE_server.cpp
 *
 * 
 * Author:    Elizabeth Acevedo
 * 
 * Date:      11/17/2025
 * 
 * Purpose: This program is the server side (Peripheral) of the bluetooth
 *          communication between my device and the app. The server advertises
 *          itself for clients (Central) to connect. It exposes a 
 *          GATT (Generic Attribute Profile) Service containing data 
 *          like sensor readings.
 * 
 * 
 * Utilization: TBD
 *
 * 
 *****************************************************************************/
/* INCLUDES */
#include <Arduino.h>
#include <BLEDevice.h>

/* DEFINES */
#define DEVICE_NAME "Guardian Pax"
#define GREEN_LED 2
#define RED_LED 5


/*** Callbacks ***/
class MyServerCallbacks : public BLEServerCallbacks {

    void onConnect(BLEServer *pServer) {    // funcs are provided
        Serial.println("Client Connected!");
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    }

    void onDisconnect(BLEServer *pServer) {
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        Serial.println("Client Disconnected!");
        BLEDevice::startAdvertising();
    }
};


void setup() {
    delay(1000); 
    Serial.begin(115200);
    Serial.println("ESP32 BLE Server setup beginning...");

    // LED Configuration
        pinMode(GREEN_LED, OUTPUT);
        pinMode(RED_LED, OUTPUT);

    // Initialize Device
    BLEDevice::init(DEVICE_NAME); 

    // Create Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    

    // Start Advertising
    BLEDevice::startAdvertising();
}

void loop() {
    delay(10);
}