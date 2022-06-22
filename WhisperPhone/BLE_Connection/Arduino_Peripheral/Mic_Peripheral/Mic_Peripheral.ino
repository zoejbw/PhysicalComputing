/*
    Uncomment or comment the line below to match the arduino you are using for acceleromter
*/

#include <Arduino_LSM9DS1.h> // For Arduino Nano 33 BLE Sense
//#include <Arduino_LSM6DS3.h> // For Arduino Nano 33 IoT

/*
    Include Bluetooth and Microphone library for Arduino
*/

#include <ArduinoBLE.h>
#include <PDM.h>

/*
    Setting up for different mic. Here is all the different UUID for Mic A and Mic B. Uncomment the code for different Mic
*/

// Mic A

char* setupName = "Mic_A";
char* serialInfo = "BLE Mic A Peripheral";
char* serviceUUID = "3480CB07-5310-4965-93DB-47425E0F7B58";
char* accelXValueUUID = "21C43457-2957-4C2D-BE75-054EF87BB806";
char* accelYValueUUID = "ED004BE4-0942-4BA4-A722-55849F297CAD";
char* accelZValueUUID = "F162F5DC-C6FC-44D4-B018-ED5DA4A5BD9F";
char* micVolUUID = "12A149F4-662D-498E-A8C8-D91C38DA9C86";

// Mic B

//char* setupName = "Mic_B";
//char* serialInfo = "BLE Mic B Peripheral";
//char* serviceUUID = "BEEA1B66-8C67-459B-8BC4-1803FD4A2353";
//char* accelXValueUUID = "73EF308A-FAC2-41CF-BB20-C4A861FA9F78";
//char* accelYValueUUID = "77EC8166-4989-42D0-8415-19725A2C1C88";
//char* accelZValueUUID = "942C0C74-6627-4C5D-81CD-239F9C118D3B";
//char* micVolUUID = "A7F36347-E5A3-40DA-A991-A50D7311FBBE";

/*
   Setting up BLE peripheral with service that contains multiple
   characteristics to read
*/

// Service and characteristics for acceleromter
BLEService micService(serviceUUID); // BLE mic level and accelerometer Service
BLEFloatCharacteristic accelXValueChar(accelXValueUUID, BLERead | BLEWrite); // BLE characteristic for accelerometer X axis value
BLEFloatCharacteristic accelYValueChar(accelYValueUUID, BLERead | BLEWrite); // BLE characteristic for accelerometer Y axis value
BLEFloatCharacteristic accelZValueChar(accelZValueUUID, BLERead | BLEWrite); // BLE characteristic for accelerometer Z axis value
BLEIntCharacteristic micVolChar(micVolUUID, BLERead | BLEWrite); // BLE characteristic for mic input

// Microphone volume setup variables

// buffer to read samples into, each sample is 16-bits
short sampleBuffer[256];

// number of samples read
volatile int samplesRead;

void setup() {

  Serial.begin(9600);

  // Configure Microphone setup

  // configure the data receive callback
  PDM.onReceive(onPDMdata);

  // initialize PDM with:
  // - one channel (mono mode)
  // - a 16 kHz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  // begin initialization for Accelerometer
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // begin initialization for BLE
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName(setupName);
  BLE.setAdvertisedService(serviceUUID);

  // add the characteristic to the service
  micService.addCharacteristic(accelXValueChar);
  micService.addCharacteristic(accelYValueChar);
  micService.addCharacteristic(accelZValueChar);
  micService.addCharacteristic(micVolChar);


  // add service
  BLE.addService(micService);

  // set the initial value for the characeristic:
  accelXValueChar.writeValue(0);
  accelYValueChar.writeValue(0);
  accelZValueChar.writeValue(0);
  micVolChar.writeValue(0);

  Serial.println(serialInfo);
  // start advertising
  BLE.advertise();

}

void loop() {

  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    while (central.connected()) {
      updateAccelValues();
      updateMicVolValues();
    }

    // while the central is not connected to peripheral:
    if (!central.connected()) {
      Serial.print(F("Disconnected from central: "));
      Serial.println(central.address());
    }

  }

}

void updateAccelValues() {
  float x, y, z;
  int degreesX = 0;
  int degreesY = 0;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    if (x > 0.1) {
      x = 100 * x;
      degreesX = map(x, 0, 97, 0, 90);
      Serial.print("Tilting up ");
      Serial.print(degreesX);
      Serial.println("  degrees");
    }
    if (x < -0.1) {
      x = 100 * x;
      degreesX = map(x, 0, -100, 0, 90);
      Serial.print("Tilting down ");
      Serial.print(degreesX);
      Serial.println("  degrees");
    }
    if (y > 0.1) {
      y = 100 * y;
      degreesY = map(y, 0, 97, 0, 90);
      Serial.print("Tilting left ");
      Serial.print(degreesY);
      Serial.println("  degrees");
    }
    if (y < -0.1) {
      y = 100 * y;
      degreesY = map(y, 0, -100, 0, 90);
      Serial.print("Tilting right ");
      Serial.print(degreesY);
      Serial.println("  degrees");
    }

    accelXValueChar.writeValue(degreesX);
    accelYValueChar.writeValue(degreesY);
    accelZValueChar.writeValue(z);
  }

}

void updateMicVolValues() {

  if (samplesRead) {

    // print samples to the serial monitor or plotter
    for (int i = 0; i < samplesRead; i++) {
     // Serial.println(sampleBuffer[i]);
      // check if the sound value is higher than 300
      if (sampleBuffer[i]>=300){
        Serial.println("high");
        micVolChar.writeValue(2);
      }
      // check if the sound value is higher than 150 and lower than 300
      if (sampleBuffer[i]>=150 && sampleBuffer[i] < 300){
        Serial.println("med");
        micVolChar.writeValue(1);
      }
      //check if the sound value is higher than 0 and lower than 150
      if (sampleBuffer[i]>=0 && sampleBuffer[i] < 150){
        Serial.println("low"); 
        micVolChar.writeValue(0);       
      }
    }
    // clear the read count
    samplesRead = 0;
  }

}

void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}
