#include <ArduinoBLE.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  130

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

//relay 1
//char* setupName = "Box_1";
//char* serialInfo = "BLE Box A Peripheral";
//char* serviceUUID = "17C55463-63CA-44B8-8268-2106F3487B7F";
//char* relayUUID = "A2492DEF-1AA4-41EA-AB67-CCB0765F076F";
//char* redUUID = "4C5E134B-85E6-4A25-AE26-4AB0EC29FC6E";
//char* greenUUID = "5516772C-1380-4876-B647-77B9188F6DB9";
//char* blueUUID = "98D873A2-D1CA-4F5B-B5AC-26925F3F0FF4";
//char* phoneSwitchUUID = "7C5343B2-1423-466C-939C-5A694C3BB765";

//relay 2
char* setupName = "Box_2";
char* serialInfo = "BLE Box B Peripheral";
char* serviceUUID = "BEEA1B66-8C67-459B-8BC4-1803FD4A2353";
char* relayUUID = "A7F36347-E5A3-40DA-A991-A50D7311FBBE";
char* redUUID = "D0832607-A4CE-4BE0-9DE3-8616B6FBD14C";
char* greenUUID = "0C6A8A55-5936-41A7-9399-83CA405D6DB1";
char* blueUUID = "E9240E9B-85FB-471B-8D0E-6BAD461B0F8C";
char* phoneSwitchUUID = "96948042-DBD7-41CC-A3A8-7D601886EDD3";

int relayOn = 2;
int relayHigh = 3;

bool isOn = false;
bool isHigh = false;

bool isVol = false;
bool isHighVol = false;

bool localPhoneSwitch = false;
const int switchPin = 7;
bool beginning = true;

int switchState = 0;

int delayVal = 250;

//Service and characteristics for acceleromter
BLEService relayService(serviceUUID); // BLE accelerometer Service
BLEIntCharacteristic relayChar(relayUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic redChar(redUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic greenChar(greenUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic blueChar(blueUUID, BLERead | BLEWrite); // BLE characteristic for
BLEIntCharacteristic phoneSwitchChar(phoneSwitchUUID, BLERead | BLEWrite); // BLE characteristic for

void setup() {

  Serial.begin(9600);
  //while (!Serial);

  pinMode(relayOn, OUTPUT);
  pinMode(relayHigh, OUTPUT);
  pinMode(switchPin, INPUT);
  digitalWrite(relayOn, LOW);
  digitalWrite(relayHigh, LOW);

  //NeoPixels
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);

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
  relayService.addCharacteristic(phoneSwitchChar);

  Serial.println(serialInfo);

  BLE.addService(relayService);

  relayChar.writeValue(0);
  redChar.writeValue(0);
  blueChar.writeValue(0);
  greenChar.writeValue(0);
  phoneSwitchChar.writeValue(0);

  // start advertising
  BLE.advertise();
}

void loop() {

  switchState = digitalRead(switchPin);
  localPhoneSwitch = switchState;

  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      //Serial.println(central.connected());

      if (phoneSwitchChar.written()) {
        //        if (phoneSwitchChar.value() == 1 && localPhoneSwitch == false && beginning == true) {
        //          openWhite(30);
        //          beginning = false;
        //        } else if (phoneSwitchChar.value() == 0 && localPhoneSwitch == false && beginning == true) {
        //          endWhite();
        //        } else if (phoneSwitchChar.value() == 1 && localPhoneSwitch == true) {
        //          UpBlueWhite(20);
        //          BlueToWarmWhite(40);
        //        } else if (phoneSwitchChar.value() == 0 && localPhoneSwitch == false) {
        //          DownWarmWhite(20);
        //          beginning == true;
        //        } else if (localPhoneSwitch == false && !beginning) {
        //          endWhite();
        //          beginning == true;
        //        }

        if (phoneSwitchChar.value() == 1) {
          openWhite(5);
        } else if (phoneSwitchChar.value() == 2) {
          UpBlueWhite(5);
        } else if (phoneSwitchChar.value() == 3) {
          BlueToWarmWhite(5);
        } else if (phoneSwitchChar.value() == 4) {
          DownWarmWhite(5);
        } else if (phoneSwitchChar.value() == 0) {
          endWhite();
        }

      }
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
        if (isVol && !isOn) {
          digitalWrite(relayOn, HIGH);
          isOn = true;
          Serial.println("relay is on");
          delay(delayVal);
        }

        //turn off
        if (!isVol && isOn) {
          digitalWrite(relayOn, LOW);
          isOn = false;
          Serial.println("relay is off");
          delay(delayVal);
        }

        //turn high
        if (isHighVol && !isHigh) {
          digitalWrite(relayHigh, HIGH);
          isHigh = true;
          Serial.println("relay is high");
          delay(delayVal);
        }

        //turn low
        if (!isHighVol && isHigh) {
          digitalWrite(relayHigh, LOW);
          isHigh = false;
          Serial.println("relay is low");
          delay(delayVal);
        }

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

void pulseWhite(uint8_t wait) {
  for (int j = 0; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(strip.gamma8(j) * 0.5, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }

  for (int j = 255; j >= 0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(strip.gamma8(j) * 0.5, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}

void UpBlueWhite(uint8_t wait) {
  for (int j = 60; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, strip.gamma8(j) * 0.5, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}

void BlueToWarmWhite(uint8_t wait) {
  for (int j = 0; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(strip.gamma8(j) * 0.5, 0, (255 * 0.5) - (strip.gamma8(j) * 0.5), 255));
    strip.show();
    delay(wait);
  }
}

void DownWarmWhite(uint8_t wait) {
  for (int j = 255; j >= 0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(strip.gamma8(j) * 0.5, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}

void endWhite() {
  strip.fill(strip.Color(0, 0, 0, 0));
  strip.show();
}

void openWhite(uint8_t wait) {
  for (int j = 0; j < 60; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, strip.gamma8(j) * 0.5, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
}
