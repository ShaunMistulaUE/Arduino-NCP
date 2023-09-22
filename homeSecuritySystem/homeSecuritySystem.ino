//++++++++++++++++++++++++++++++++++++++++++++++//
// Home Security System Mistula|Recio 09/2023 //
//++++++++++++++++++++++++++++++++++++++++++++++//

//Libraries
#include <DHT22.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BH1750.h>
#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>


//RFID Define
#define RST_PIN 9
#define SS_PIN 10
byte readCard[4];
String tag_UID = "AFF8FA29";
String tagID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);
#define LED_red 5
#define LED_green 4
#define btn_Reset 3
#define buzzer 2

int attempt = 1;
int attempt_bool = true;

//Gas Sensor
#define gasI A3



//SENSORS Define
#define waterI A0
#define pirI 8
#define waterI_power 7
#define DHTPIN 6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


//PinSetup
Servo myservoOne;
Servo myservoTwo;

int stopperClose = 0;
int stopperOpen = 0;


void setup() {
  //RFID
  pinMode(LED_red, OUTPUT);    //WRONG RFID
  pinMode(LED_green, OUTPUT);  //RIGHT RFID
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  //Servo Motor
  myservoOne.attach(A1);
  myservoTwo.attach(A2);

  //Water Sensor
  // pinMode(waterI_power, OUTPUT);
  // digitalWrite(waterI_power, LOW);
}

void loop() {
  //RFID CODE
  while (readID()) {
    if (tagID == tag_UID) {
      digitalWrite(LED_red, LOW);
      digitalWrite(LED_green, HIGH);
      delay(130);
      digitalWrite(LED_green, LOW);
      delay(130);
      digitalWrite(LED_green, HIGH);
      delay(130);
      digitalWrite(LED_green, LOW);
      delay(130);
      digitalWrite(LED_green, HIGH);
      delay(130);
      digitalWrite(LED_green, LOW);
      delay(130);
      digitalWrite(LED_green, HIGH);
      delay(2000);
      digitalWrite(LED_green, LOW);
      attempt = 1;

    } else if (tagID != tag_UID) {
      digitalWrite(LED_green, LOW);

      if (attempt == 1) {
        digitalWrite(LED_red, HIGH);
        delay(130);
        digitalWrite(LED_red, LOW);
        delay(130);
        digitalWrite(LED_red, HIGH);
        Serial.println("I am one");
        delay(2000);
        attempt = attempt + 1;

      } else if (attempt == 2) {
        digitalWrite(LED_red, HIGH);
        delay(130);
        digitalWrite(LED_red, LOW);
        delay(130);
        digitalWrite(LED_red, HIGH);
        delay(130);
        digitalWrite(LED_red, LOW);
        delay(130);
        digitalWrite(LED_red, HIGH);
        delay(130);
        digitalWrite(LED_red, LOW);
        delay(130);
        digitalWrite(LED_red, HIGH);
        Serial.println("I am two");
        delay(2000);
        attempt = attempt + 1;
        attempt_bool = true;

      } else if (attempt == 3) {
        while (attempt_bool == true) {
          digitalWrite(LED_red, HIGH);
          delay(130);
          digitalWrite(LED_red, LOW);
          delay(130);

          Serial.println("I am three");
          //Reset Button
          int buttonState = digitalRead(btn_Reset);
          if (buttonState == 1) {
            attempt = 1;
            attempt_bool = false;
          } else {
          }
        }
      }
    }
  }

  //Gas Sensor Code
  unsigned int sensorVal = analogRead(gasI);
  unsigned int outputVal = map(sensorVal, 0, 1023, 0, 255);
  Serial.print("Gas Sensor: ");
  Serial.println(outputVal);
  delay(500);

  if (outputVal > 1) {
    myservoOne.write(10);
    myservoTwo.attach(A2);

    if (stopperClose == 1) {
      myservoTwo.write(145);
      stopperClose = 0;
      Serial.println("I am at stopper if 1");

      }
    else {
      myservoTwo.detach();
      }
    stopperOpen = 1;
    
  }
  else {
    myservoTwo.attach(A2);
    if (stopperOpen == 1) {
      myservoTwo.write(0);
      stopperOpen = 0;
      Serial.println("I am at stopper if 2");
      } 
    else {
      myservoTwo.detach();
      }
    myservoOne.write(120);

    delay(500);
    stopperClose = 1;
    myservoTwo.detach();
  }
}

//read for ID
boolean readID() {
  //Check if a new tag is detected or not. If not return.
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  //Check if a new tag is readable or not. If not return.
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  tagID = "";
  // Read the 4 byte UID
  for (uint8_t i = 0; i < 4; i++) {
    //readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));  // Convert the UID to a single String
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA();  // Stop reading
  return true;
}
