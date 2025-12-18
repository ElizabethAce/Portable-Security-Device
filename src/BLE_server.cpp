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
 * Utilization: (Using an app for testing before creating my own client device)
 *              1. Download LightBle app. 
 *              2. Build and upload code to board.
 *              3. Connect to "GuardianPax." 
 *              4. Check for services, characteristics, descriptors
 *
 * 
 *****************************************************************************/
/* INCLUDES */
#include <Arduino.h>
#include <NimBLEDevice.h>

/* DEFINES */
#define DEVICE_NAME "Guardian Pax"
#define SERVICE_UUID "5d180b5b-39a6-4478-840f-7006b6588531"     // Universaly Unique Identifier
#define CHARSTIC_UUID "d0f407a8-86e5-434b-b2b7-68826b33a76e"
//#define DESCR_UUID "4eb6a0c1-244f-4b5b-b9e6-db809522e3c1"
#define GREEN_LED 21
#define RED_LED 15


/*** Callbacks ***/
class MyServerCallbacks : public NimBLEServerCallbacks {

    void onConnect(NimBLEServer *pServer) {    // funcs are provided
        Serial.println("Client Connected!");
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    }

    void onDisconnect(NimBLEServer *pServer) {
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        Serial.println("Client Disconnected!");
        NimBLEDevice::startAdvertising();
    }
};

class MyCharacteristicCallbacks : public NimBLECharacteristicCallbacks {
    void onRead(NimBLECharacteristic *pCharacteristic) {
        uint32_t currMs = millis() / 1000;  // Displays number of seconds since connected (keeps cnting)
        pCharacteristic->setValue(currMs);
    }
};

void setup() {
    Serial.begin(115200);
    delay(1000); 
    // while (!Serial) {
    //     delay(10);
    // }
    Serial.println("ESP32 BLE Server setup beginning...");

    // LED Configuration
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    // Initialize LED state
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);

    // Initialize Device
    NimBLEDevice::init(DEVICE_NAME); 

    // Create Server
    NimBLEServer *pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    
    // Services
    NimBLEService *pService = pServer->createService(SERVICE_UUID);

    // Characteristics
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARSTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE
    );

    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

    // // Descriptor
    // BLE2901 *pDescr_2901 = new BLE2901();
    // pDescr_2901->setDescription("Time Since Device Connected:");
    // pCharacteristic->addDescriptor(pDescr_2901);


    pService->start();

    // Start Advertising
    NimBLEDevice::startAdvertising();
}

void loop() {
    delay(10);
}