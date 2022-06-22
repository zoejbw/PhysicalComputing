#include <ArduinoBLE.h>

//relay 1
//char* setupName = "Box_1";
//char* serialInfo = "BLE Box A Peripheral";
//char* serviceUUID = "17C55463-63CA-44B8-8268-2106F3487B7F";
//char* relayUUID = "A2492DEF-1AA4-41EA-AB67-CCB0765F076F";
//char* redUUID = "4C5E134B-85E6-4A25-AE26-4AB0EC29FC6E";
//char* greenUUID = "5516772C-1380-4876-B647-77B9188F6DB9";
//char* blueUUID = "98D873A2-D1CA-4F5B-B5AC-26925F3F0FF4";
//char* whiteUUID = "7C5343B2-1423-466C-939C-5A694C3BB765";

//relay 2
char* setupName = "Box_2";
char* serialInfo = "BLE Box B Peripheral";
char* serviceUUID = "BEEA1B66-8C67-459B-8BC4-1803FD4A2353";
char* relayUUID = "A7F36347-E5A3-40DA-A991-A50D7311FBBE";
char* redUUID = "D0832607-A4CE-4BE0-9DE3-8616B6FBD14C";
char* greenUUID = "0C6A8A55-5936-41A7-9399-83CA405D6DB1";
char* blueUUID = "E9240E9B-85FB-471B-8D0E-6BAD461B0F8C";
char* whiteUUID = "96948042-DBD7-41CC-A3A8-7D601886EDD3";

int relayOn = 2;
int relayHigh = 3;

bool isOn = false;
bool isHigh = false;

bool isVol = false;
bool isHighVol = false;

int delayVal = 250;

//Service and characteristics for acceleromter
BLEService relayService(serviceUUID); // BLE accelerometer Service
BLEIntCharacteristic relayChar(relayUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic redChar(redUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic greenChar(greenUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic blueChar(blueUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic whiteChar(whiteUUID, BLERead | BLEWrite); // BLE characteristic for

void setup() {

  Serial.begin(9600);
  //while (!Serial);

  pinMode(relayOn, OUTPUT);
  pinMode(relayHigh, OUTPUT);
  digitalWrite(relayOn, LOW);
  digitalWrite(relayHigh, LOW);

  // begin initialization for BLE
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName(setupName);
  BLE.setAdvertisedService(serviceUUID);

  // add the characteristic to the service
  relayService.addCharacteristic(relayChar);
  relayService.addCharacteristic(redChar);
  relayService.addCharacteristic(blueChar);
  relayService.addCharacteristic(greenChar);
  relayService.addCharacteristic(whiteChar);

  Serial.println(serialInfo);

  BLE.addService(relayService);

  relayChar.writeValue(0);
  redChar.writeValue(0);
  blueChar.writeValue(0);
  greenChar.writeValue(0);
  whiteChar.writeValue(0);

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
      //Serial.println(central.connected());
      if (relayChar.written()) {
        //Serial.println("written");
        if (relayChar.value() == 0) {
          isVol = false;
          isHighVol = false;
        } else if (relayChar.value() == 1) {
          isVol = true;
          isHighVol = false;
        } else {
          isVol = true;
          isHighVol = true;
        }

        //turn on 
        if(isVol && !isOn){
            digitalWrite(relayOn, HIGH);
            isOn = true;
            Serial.println("relay is on");
            delay(delayVal);}
            
        //turn off
        if(!isVol && isOn){
            digitalWrite(relayOn, LOW);
            isOn = false;
            Serial.println("relay is off");
            delay(delayVal);}
            
        //turn high
        if(isHighVol && !isHigh){
            digitalWrite(relayHigh, HIGH);
            isHigh = true;
            Serial.println("relay is high");
            delay(delayVal);}
            
        //turn low
        if(!isHighVol && isHigh){
            digitalWrite(relayHigh, LOW);
            isHigh = false;
            Serial.println("relay is low");
            delay(delayVal);}
            
      }
    }
  }

  //turn on
  //  digitalWrite(relayOn, HIGH);
  //  //turn high
  //  digitalWrite(relayHigh, HIGH);
  //  //turn low
  //  digitalWrite(relayHigh, LOW);
  //  //turn off
  //  digitalWrite(relayOn, LOW);
}
