/*
    Uncomment or comment the line below to match the arduino you are using for acceleromter
*/

#include <Arduino_LSM9DS1.h> // For Arduino Nano 33 BLE
//#include <Arduino_LSM6DS3.h> // For Arduino Nano 33 IoT

/*
   Setting up for different player. Here is all the different UUID for player 1 to 4. Uncomment the code for different player
*/

// Player1

char* playerName = "Player_1";
char* serialInfo = "BLE Player 1 Peripheral";
char* serviceUUID = "8EF0E0A7-1807-4458-882D-74899FD040A2";
char* accelXValueUUID = "55E61D33-F804-4714-93C1-0481B91928A4";
char* accelYValueUUID = "91605431-76CE-4A37-9480-80DF67A1A9C7C";
char* accelZValueUUID = "76E675C8-4E48-41BF-89B2-6808745A101A";
char* accelFlapUpUUID = "B147F299-B112-4785-AE1F-5686EC0BDE77";
char* accelFlapDownUUID = "1A5B4BE6-6791-4EBA-A416-8FC7938914EC";
char* accelCountUUID = "0CBE7D9E-707E-422E-8803-B1F9D27A830C";
char* switchUUID = "5EE04DE8-22B1-4227-BC09-20D564410F5D";

// Player2

//char* playerName = "Player_2";
//char* serialInfo = "BLE Player 2 Peripheral";
//char* serviceUUID = "B64E61EA-EAE3-4549-99C4-126C66272F59";
//char* accelXValueUUID = "A2492DEF-1AA4-41EA-AB67-CCB0765F076F";
//char* accelYValueUUID = "4C5E134B-85E6-4A25-AE26-4AB0EC29FC6E";
//char* accelZValueUUID = "981E05F0-FA94-42AC-8D5F-9245090DDD9B";
//char* accelFlapUpUUID = "A60D4BDF-E90A-40AF-8BF9-15E7D8086C86";
//char* accelFlapDownUUID = "17C55463-63CA-44B8-8268-2106F3487B7F";
//char* accelCountUUID = "3FFF957B-BE12-45FC-8F2F-F2596A5D638C";
//char* switchUUID = "53308B5A-D3D1-4F4B-A10F-90970E242C12";


// Player3

//char* playerName = "Player_3";
//char* serialInfo = "BLE Player 3 Peripheral";
//char* serviceUUID = "4E3EC1F5-0E6C-40CF-8F72-AC88DA2CDFC2";
//char* accelXValueUUID = "E53F711A-5EB4-43A8-83FD-7F18170D2AF8";
//char* accelYValueUUID = "09DB8637-7D46-4D7E-8414-7DED75B49A3C";
//char* accelZValueUUID = "A2621E62-AAB3-49E1-AD71-65F368FFB91C";
//char* accelFlapUpUUID = "4BB959E0-3BE4-4952-8E0E-F123A68A985C";
//char* accelFlapDownUUID = "C5E4FEE3-C873-4046-AB48-F34464437E39";
//char* accelCountUUID = "E6E4FB63-6F8E-4E23-AE17-5DBA4CE4B527";
//char* switchUUID = "3A09CCB5-22DA-4CFD-9626-BD73FB34AE1A";

// Player4

//char* playerName = "Player_4";
//char* serialInfo = "BLE Player 4 Peripheral";
//char* serviceUUID = "99C99D32-C7E8-4E72-9ADF-B3016DCDB018";
//char* accelXValueUUID = "420318CD-CC64-4821-BF98-BD7C1FDB5ABC";
//char* accelYValueUUID = "02FC0172-7D67-47E6-B692-6DBD84375DB1";
//char* accelZValueUUID = "45D3B87A-9ECF-4408-AC57-D97994D525BC";
//char* accelFlapUpUUID = "B6B54D31-9B2C-471D-89C1-5D173B63EF30";
//char* accelFlapDownUUID = "EFB10C21-0E77-463F-96DC-0F5D2EDB1E89";
//char* accelCountUUID = "C561E4CE-56AF-47C3-A666-40143C4AEF6A";
//char* switchUUID = "7A05AE26-0AF7-4FA8-8365-C074FE0AF719";



/*
   Setting up BLE peripheral with service that contains a
   characteristic to read from accelerometer
*/

#include <ArduinoBLE.h>

//Service and characteristics for acceleromter
BLEService playerService(serviceUUID); // BLE accelerometer Service
BLEFloatCharacteristic accelXValueChar(accelXValueUUID, BLERead); // BLE characteristic for accelerometer X axis value
BLEFloatCharacteristic accelYValueChar(accelYValueUUID, BLERead); // BLE characteristic for accelerometer Y axis value
BLEFloatCharacteristic accelZValueChar(accelZValueUUID, BLERead); // BLE characteristic for accelerometer Z axis value
BLEFloatCharacteristic accelFlapUpChar(accelFlapUpUUID, BLERead); // BLE characteristic for accelerometer Z axis value
BLEFloatCharacteristic accelFlapDownChar(accelFlapDownUUID, BLERead); // BLE characteristic for accelerometer Z axis value
BLEIntCharacteristic accelCountChar(accelCountUUID, BLERead); // BLE characteristic for wings flapping count
BLEBoolCharacteristic switchChar(switchUUID, BLERead); // BLE characteristic for switch

int flaps = 0;
bool flappedDown = false;

int switchPin = 2;

void setup() {

  Serial.begin(9600);
  //while (!Serial);

  pinMode(switchPin, INPUT);

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
  BLE.setLocalName(playerName);
  BLE.setAdvertisedService(serviceUUID);

  // add the characteristic to the service
  playerService.addCharacteristic(accelXValueChar);
  playerService.addCharacteristic(accelYValueChar);
  playerService.addCharacteristic(accelZValueChar);
  playerService.addCharacteristic(accelFlapUpChar);
  playerService.addCharacteristic(accelFlapDownChar);
  playerService.addCharacteristic(accelCountChar);
  playerService.addCharacteristic(switchChar);

  // add service
  BLE.addService(playerService);

  // set the initial value for the characeristic:
  accelXValueChar.writeValue(0);
  accelYValueChar.writeValue(0);
  accelZValueChar.writeValue(0);
  accelFlapUpChar.writeValue(-0.20);
  accelFlapDownChar.writeValue(-0.90);
  accelCountChar.writeValue(0);
  switchChar.writeValue(false);

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

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to reset the flapping count:
      if (switchChar.written()) {
        //Serial.println(accelCountChar.value());
        if ( switchChar.value() == true) {   //  0
          Serial.println("Flapping count reset to 0");
          flaps = 0;
          switchChar.writeValue(false);
          return;
        } else {                              // not a 0 value
          Serial.println(F("Someting is wrong?!"));
        }
        Serial.println(F("Someting is wrong?!"));
        return;
      }
      updateAccelValues();
      //switchChar.writeValue(switchDetect(switchPin));
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }

}

void updateAccelValues() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

        Serial.print("Accel Reading: ");
        Serial.print(x);
        Serial.print('\t');
        Serial.print(y);
        Serial.print('\t');
        Serial.println(z);
        Serial.print("Flap Counting: ");
        Serial.println(flaps);

    accelXValueChar.writeValue(x);
    accelXValueChar.writeValue(y);
    accelXValueChar.writeValue(z);
    accelCountChar.writeValue(flappingCount(x));;

  }

}

int switchDetect (int pin) {
  if (digitalRead(pin) == HIGH) {
    //Serial.println("button Pressed");
    return 1;
  } else {
    return 0;
  }
}

int flappingCount(float changeValue) {

  if (changeValue <= accelFlapDownChar.value() && flappedDown == false ) {
    flaps++;
    flappedDown = true;
    Serial.println(flaps);
  } else if (changeValue >= accelFlapUpChar.value() && flappedDown == true) {
    flappedDown = false;
  } else {
    
  }
  return flaps;
}
