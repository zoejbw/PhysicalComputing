//player1 Bluetooth Setup Variables
let p1ServiceUuid = "3480CB07-5310-4965-93DB-47425E0F7B58";
//let p1SwitchCountUuid = "12A149F4-662D-498E-A8C8-D91C38DA9C86";
let p1AccelCountUuid = "12A149F4-662D-498E-A8C8-D91C38DA9C86";
let p1AccelCharacteristic;
let p1SwitchCharacteristic;
let p1AccelValue = 0;
let p1SwitchValue = false;
let player1BLE;
let p1CharNum;

//player2 Bluetooth Setup Variables
let p2ServiceUuid = "BEEA1B66-8C67-459B-8BC4-1803FD4A2353";
//let p2SwitchCountUuid = "A7F36347-E5A3-40DA-A991-A50D7311FBBE";
let p2AccelCountUuid = "A7F36347-E5A3-40DA-A991-A50D7311FBBE";
let p2AccelCharacteristic;
let p2SwitchCharacteristic;
let p2AccelValue = 0;
let p2SwitchValue = false;
let player2BLE;
let p2CharNum;

// box 1 Bluetooth Setup Variables
let box1ServiceUuid = "17C55463-63CA-44B8-8268-2106F3487B7F";
let box1relayUuid = "A2492DEF-1AA4-41EA-AB67-CCB0765F076F";
let box1redUuid = "4C5E134B-85E6-4A25-AE26-4AB0EC29FC6E";
let box1greenUuid = "5516772C-1380-4876-B647-77B9188F6DB9";
let box1blueUuid = "98D873A2-D1CA-4F5B-B5AC-26925F3F0FF4";
let box1PhoneSwitchUuid = "7C5343B2-1423-466C-939C-5A694C3BB765";
let box1RelayCharacteristic;
let box1RedCharacteristic;
let box1GreenCharacteristic;
let box1BlueCharacteristic;
let box1PhoneSwitchCharacteristic;
let box1BLE;
let box1CharNum;
let box1Connected = false;

// box 2 Bluetooth Setup Variables
let box2ServiceUuid = "BEEA1B66-8C67-459B-8BC4-1803FD4A2353";
let box2relayUuid = "A7F36347-E5A3-40DA-A991-A50D7311FBBE";
let box2redUuid = "D0832607-A4CE-4BE0-9DE3-8616B6FBD14C";
let box2greenUuid = "0C6A8A55-5936-41A7-9399-83CA405D6DB1";
let box2blueUuid = "E9240E9B-85FB-471B-8D0E-6BAD461B0F8C";
let box2PhoneSwitchUuid = "96948042-DBD7-41CC-A3A8-7D601886EDD3";
let box2RelayCharacteristic;
let box2RedCharacteristic;
let box2GreenCharacteristic;
let box2BlueCharacteristic;
let box2PhoneSwitchCharacteristic;
let box2BLE;
let box2CharNum;
let box2Connected = false;

// Set up for the p5 game

let connectP1Button;
let connectP2Button;
let connectBox1Button;
let connectBox2Button;
let relay1Button;
let relay2Button;
let color2OpenButton;
let color2UpBlueButton;
let color2BtoWButton;
let color2DownWarmButton;
let color2EndButton;

//setup for avging volume
let timesloop = 50;
let numloops = 0;
let totalVol = 0;
let roundVol = 0;

//setup for avging volume
let numloops2 = 0;
let totalVol2 = 0;
let roundVol2 = 0;

let first = false;

//bletooth init and canvas setup
function setup() {
  // Create a p5ble class
  p1ServiceUuid = p1ServiceUuid.toLowerCase();
  player1BLE = new p5ble();

  connectP1Button = createButton("Player 1");
  connectP1Button.center();
  connectP1Button.position(windowWidth / 2, windowHeight / 1.8);
  connectP1Button.mousePressed(connectToP1Ble);

  p2ServiceUuid = p2ServiceUuid.toLowerCase();
  player2BLE = new p5ble();

  connectP2Button = createButton("Player 2");
  connectP2Button.center();
  connectP2Button.position(windowWidth / 2.4, windowHeight / 1.8);
  connectP2Button.mousePressed(connectToP2Ble);

  box1ServiceUuid = box1ServiceUuid.toLowerCase();
  box1BLE = new p5ble();

  connectBox1Button = createButton("Box 1");
  connectBox1Button.center();
  connectBox1Button.position(windowWidth / 2, windowHeight / 2.2);
  connectBox1Button.mousePressed(connectToBox1Ble);

  box2ServiceUuid = box2ServiceUuid.toLowerCase();
  box2BLE = new p5ble();

  connectBox2Button = createButton("Box 2");
  connectBox2Button.center();
  connectBox2Button.position(windowWidth / 2, windowHeight / 2);
  connectBox2Button.mousePressed(connectToBox2Ble);

  relay1Button = createButton("Relay 1 write");
  relay1Button.center();
  relay1Button.position(windowWidth / 2.4, windowHeight / 2.2);
  relay1Button.mousePressed(testing);

  relay2Button = createButton("Relay 2 write");
  relay2Button.center();
  relay2Button.position(windowWidth / 2.4, windowHeight / 2);
  relay2Button.mousePressed(testing2);

  color2OpenButton = createButton("Color 2 open");
  color2OpenButton.center();
  color2OpenButton.position(windowWidth / 2.4, windowHeight / 2.6);
  color2OpenButton.mousePressed(testinglight1);

  color2UpBlueButton = createButton("Color 2 up blue");
  color2UpBlueButton.center();
  color2UpBlueButton.position(windowWidth / 2.4, windowHeight / 2.8);
  color2UpBlueButton.mousePressed(testinglight2);

  color2BtoWButton = createButton("Color 2 b to w");
  color2BtoWButton.center();
  color2BtoWButton.position(windowWidth / 2.4, windowHeight / 3);
  color2BtoWButton.mousePressed(testinglight3);

  color2DownWarmButton = createButton("Color 2 dim down");
  color2DownWarmButton.center();
  color2DownWarmButton.position(windowWidth / 2.4, windowHeight / 3.2);
  color2DownWarmButton.mousePressed(testinglight4);

  color2EndButton = createButton("Color 2 end");
  color2EndButton.center();
  color2EndButton.position(windowWidth / 2.4, windowHeight / 3.4);
  color2EndButton.mousePressed(testinglight0);

  createCanvas(windowWidth, windowHeight);
}

function testing() {

  box1RelaySend(2);

}

function testing2() {

  box2RelaySend(2);

}

function testinglight1() {

  box2PhoneSwitchSend(1);

}

function testinglight2() {

  box2PhoneSwitchSend(2);

}

function testinglight3() {

  box2PhoneSwitchSend(3);

}

function testinglight4() {

  box2PhoneSwitchSend(4);

}

function testinglight0() {

  box2PhoneSwitchSend(0);

}

function connectToP1Ble() {
  // Connect to a device by passing the service UUID
  player1BLE.connect(p1ServiceUuid, gotP1Characteristics);
}

function connectToP2Ble() {
  // Connect to a device by passing the service UUID
  player2BLE.connect(p2ServiceUuid, gotP2Characteristics);
}

function connectToBox1Ble() {
  // Connect to a device by passing the service UUID
  box1BLE.connect(box1ServiceUuid, gotBox1Characteristics);
}

function connectToBox2Ble() {
  // Connect to a device by passing the service UUID
  box2BLE.connect(box2ServiceUuid, gotBox2Characteristics);
}

// A function that will be called once got characteristics
function gotBox1Characteristics(error, characteristics) {
  if (error) console.log("error: ", error);
  console.log("characteristics: ", characteristics);
  for (let i = 0; i < characteristics.length; i++) {
    if (characteristics[i].uuid == box1relayUuid.toLowerCase()) {
      //box1Connected = true;
      box1CharNum = i;
      console.log(`Box 1 relay ${i} is working`);
      console.log(characteristics[i].uuid);
      box1RelayCharacteristic = characteristics[box1CharNum];
    } else {}
    if (characteristics[i].uuid == box1redUuid.toLowerCase()) {
      box1CharNum = i;
      console.log(`Box 1 Red ${i} is working`);
      console.log(characteristics[i].uuid);
      box1RedCharacteristic = characteristics[box1CharNum];
    } else {}
    if (characteristics[i].uuid == box1greenUuid.toLowerCase()) {
      box1CharNum = i;
      console.log(`Box 1 Green ${i} is working`);
      console.log(characteristics[i].uuid);
      box1GreenCharacteristic = characteristics[box1CharNum];
    } else {}
    if (characteristics[i].uuid == box1blueUuid.toLowerCase()) {
      box1CharNum = i;
      console.log(`Box 1 Blue ${i} is working`);
      console.log(characteristics[i].uuid);
      box1BlueCharacteristic = characteristics[box1CharNum];
    } else {}
    if (characteristics[i].uuid == box1PhoneSwitchUuid.toLowerCase()) {
      box1CharNum = i;
      console.log(`Box 1 White ${i} is working`);
      console.log(characteristics[i].uuid);
      box1PhoneSwitchCharacteristic = characteristics[box1CharNum];
    } else {
      continue;
    }
  }
}

// A function that will be called once got characteristics
function gotBox2Characteristics(error, characteristics) {
  if (error) console.log("error: ", error);
  console.log("characteristics: ", characteristics);
  for (let i = 0; i < characteristics.length; i++) {
    if (characteristics[i].uuid == box2relayUuid.toLowerCase()) {
      //box2Connected = true;
      box2CharNum = i;
      console.log(`Box 2 relay ${i} is working`);
      console.log(characteristics[i].uuid);
      box2RelayCharacteristic = characteristics[box2CharNum];
    } else {}
    if (characteristics[i].uuid == box2redUuid.toLowerCase()) {
      box2CharNum = i;
      console.log(`Box 2 Red ${i} is working`);
      console.log(characteristics[i].uuid);
      box2RedCharacteristic = characteristics[box2CharNum];
    } else {}
    if (characteristics[i].uuid == box2greenUuid.toLowerCase()) {
      box2CharNum = i;
      console.log(`Box 2 Green ${i} is working`);
      console.log(characteristics[i].uuid);
      box2GreenCharacteristic = characteristics[box2CharNum];
    } else {}
    if (characteristics[i].uuid == box2blueUuid.toLowerCase()) {
      box2CharNum = i;
      console.log(`Box 2 Blue ${i} is working`);
      console.log(characteristics[i].uuid);
      box2BlueCharacteristic = characteristics[box2CharNum];
    } else {}
    if (characteristics[i].uuid == box2PhoneSwitchUuid.toLowerCase()) {
      box2CharNum = i;
      console.log(`Box 2 White ${i} is working`);
      console.log(characteristics[i].uuid);
      box2PhoneSwitchCharacteristic = characteristics[box2CharNum];
    } else {
      continue;
    }
  }
}

// A function that will be called once got characteristics
function gotP1Characteristics(error, characteristics) {
  if (error) console.log("error: ", error);
  console.log("characteristics: ", characteristics);
  for (let i = 0; i < characteristics.length; i++) {
    if (characteristics[i].uuid == p1AccelCountUuid.toLowerCase()) {
      p1CharNum = i;
      console.log(`Accel Number ${i} is working`);
      console.log(characteristics[i].uuid);
      p1AccelCharacteristic = characteristics[p1CharNum];
    } else {
      continue;
    }
    // if (characteristics[i].uuid == p1SwitchCountUuid.toLowerCase()) {
    //   p1CharNum = i;
    //   console.log(`Switch Number ${i} is working`);
    //   console.log(characteristics[i].uuid);
    //   p1SwitchCharacteristic = characteristics[p1CharNum];
    // } else {
    //   continue;
    // }
    player1BLE.read(p1AccelCharacteristic, gotP1AccelValue);
    //player1BLE.read(p1SwitchCharacteristic, gotP1SwitchValue);
  }
}

function gotP2Characteristics(error, characteristics) {
  if (error) console.log("error: ", error);
  console.log("characteristics: ", characteristics);
  for (let i = 0; i < characteristics.length; i++) {
    if (characteristics[i].uuid == p2AccelCountUuid.toLowerCase()) {
      p2CharNum = i;
      console.log(`Accel Number ${i} is working`);
      console.log(characteristics[i].uuid);
      p2AccelCharacteristic = characteristics[p2CharNum];
    } else {
      continue;
    }
    // if (characteristics[i].uuid == p2SwitchCountUuid.toLowerCase()) {
    //   p2CharNum = i;
    //   console.log(`Switch Number ${i} is working`);
    //   console.log(characteristics[i].uuid);
    //   p2SwitchCharacteristic = characteristics[p2CharNum];
    // } else {
    //   continue;
    // }
    player2BLE.read(p2AccelCharacteristic, gotP2AccelValue);
    //player2BLE.read(p2SwitchCharacteristic, gotP2SwitchValue);
  }
}

// A function that will be called once got values
function gotP1AccelValue(error, value) {
  if (error) console.log("error: ", error);
  console.log("p1AccelValue: ", value);
  p1AccelValue = value;
  player1BLE.read(p1AccelCharacteristic, gotP1AccelValue);
}

function gotP2AccelValue(error, value) {
  if (error) console.log("error: ", error);
  console.log("p2AccelValue: ", value);
  p2AccelValue = value;
  player2BLE.read(p2AccelCharacteristic, gotP2AccelValue);
}

// function gotP1SwitchValue(error, value) {
//   if (error) console.log("error: ", error);
//   //console.log("p1SwitchValue: ", value);
//   p1SwitchValue = value;
//   player1BLE.read(p1SwitchCharacteristic, gotP1SwitchValue);
// }

// game on p5 sketch
function draw() {
  if (box2BLE.isConnected() && player1BLE.isConnected()) {
    calcVol();
  }
  if (box1BLE.isConnected() && player2BLE.isConnected()) {
    calcVol2();
  }
  screen0();
}

function screen0() {
  if (player1BLE.isConnected() || player2BLE.isConnected()) {
    clear();
    push();
    background(255);
    textSize(windowWidth * 0.05);
    textAlign(CENTER);
    text(roundVol, windowWidth / 2, windowHeight / 2);
    text(roundVol2, (windowWidth / 2) + 50, windowHeight / 2);
    pop();
  } else {
    push();
    background(255);
    textSize(windowWidth * 0.05);
    textAlign(CENTER);
    text("waiting players to connect...", windowWidth / 2, windowHeight / 2);
    pop();
  }
}

function calcVol() {
  if (numloops < timesloop) {
    totalVol += p1AccelValue;
    numloops++;
  } else {
    //update round vol
    //if (box2BLE.isConnected() || player1BLE.isConnected()) {
    if ((totalVol / timesloop) >= 1.25) {
      roundVol = 2;
      box2RelaySend(2);
    } else if ((totalVol / timesloop) >= 0.25) {
      roundVol = 1;
      box2RelaySend(1);
    } else {
      roundVol = 0;
      box2RelaySend(0);
    }
    //}

    numloops = 0;
    totalVol = 0;
  }

}

function calcVol2() {
  if (numloops2 < timesloop) {
    totalVol2 += p2AccelValue;
    numloops2++;
  } else {
    //if (box1BLE.isConnected() || player2BLE.isConnected()) {
    if ((totalVol2 / timesloop) >= 1.25) {
      roundVol2 = 2;
      box1RelaySend(2);
    } else if ((totalVol2 / timesloop) >= 0.25) {
      roundVol2 = 1;
      box1RelaySend(1);
    } else {
      roundVol2 = 0;
      box1RelaySend(0);
    }
    //}

    numloops2 = 0;
    totalVol2 = 0;
  }

}

function box1RelaySend(relayState) {
  box1BLE.write(box1RelayCharacteristic, relayState);
}

function box2RelaySend(relayState) {
  box2BLE.write(box2RelayCharacteristic, relayState);
}

function box1RedSend(Red) {
  box1BLE.write(box1RedCharacteristic, Red);
}

function box2RedSend(Red) {
  box2BLE.write(box2RedCharacteristic, Red);
}

function box1GreenSend(Green) {
  box1BLE.write(box1GreenCharacteristic, Green);
}

function box2GreenSend(Green) {
  box2BLE.write(box2GreenCharacteristic, Green);
}

function box1BlueSend(Blue) {
  box1BLE.write(box1BlueCharacteristic, Blue);
}

function box2BlueSend(Blue) {
  box2BLE.write(box2BlueCharacteristic, Blue);
}

function box1PhoneSwitchSend(White) {
  box1BLE.write(box1PhoneSwitchCharacteristic, White);
}

function box2PhoneSwitchSend(White) {
  box2BLE.write(box2PhoneSwitchCharacteristic, White);
}