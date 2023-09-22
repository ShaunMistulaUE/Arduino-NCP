//++++++++++++++++++++++++++++++++++++++++++++++//
// Home Automation System Mistula|Recio 09/2023 //
//++++++++++++++++++++++++++++++++++++++++++++++//

//Libraries
#include <DHT22.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BH1750.h>
#include <Wire.h>
#include <Servo.h>

//PinSetup
Servo myservoOne;
Servo myservoTwo;
BH1750 GY30;
#define pirI 13
#define irI 12
#define buzzer 9
#define doorBell 7
#define DHTPIN 6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define light 3
#define rainI A0

//lights for temperature
#define led_1 8
#define led_2 5
#define led_3 4
#define led_4 2
#define led_5 A1

//int
int pirVal = 0;
int rainVal = 0;
int serVal = 0;
int stopperClose = 0;
int stopperOpen = 0;
float humid = 0;
float temp = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  GY30.begin();
  dht.begin();
  myservoOne.attach(11);
  myservoTwo.attach(10);

  //pinMode
  pinMode(light, OUTPUT);
  pinMode(pirI, INPUT);
  pinMode(irI, INPUT);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
}

void loop() {
  Serial.println("+++++++++++++++");

  //Humidity and Temperature value
  temp = dht.readTemperature();
  Serial.print(" Temperature : ");
  Serial.println(temp);

  tempLED(temp);




  //Doorbell(btn)
  int buttonState = digitalRead(doorBell);
  if (buttonState == 1) {
    tone(buzzer, 660);
    delay(700);
    tone(buzzer, 550);
    delay(700);
    tone(buzzer, 440);
    delay(700);
    noTone(buzzer);
    noTone(buzzer);
  } else {
    noTone(buzzer);
    Serial.println(buttonState);
  }

  //light sensor
  float lux = GY30.readLightLevel();
  Serial.println((String) "Light: " + lux + " lx");

  //rainDrop value
  rainVal = readSensor();
  Serial.print("RainDrop: ");
  Serial.println(rainVal);


  //IR value
  int irVal = digitalRead(irI);
  Serial.print("IR : ");
  Serial.println(irVal);


  //IR && Servo controller
  if (irVal == 1) {
    myservoOne.write(10);
    myservoTwo.attach(10);

    //360 servo stopper (close)
    if (stopperClose == 1) {  // prevents the servo from looping
      myservoTwo.write(145);
      stopperClose = 0;
    } else {
      myservoTwo.detach();
    }

    stopperOpen = 1;

    delay(1000);
  } else {
    myservoTwo.attach(10);

    //360 servo stopper (open)
    if (stopperOpen == 1) {  //prevents the servo from looping
      myservoTwo.write(0);
      stopperOpen = 0;
    } else {
      myservoTwo.detach();
    }
    myservoOne.write(120);

    delay(500);
    stopperClose = 1;
    myservoTwo.detach();
  }

  //PiR value
  pirVal = digitalRead(pirI);

  //PiR Function (Lights == HIGH(on) if(User = True) else(lights off))
  if (pirVal == HIGH) {
    if ((lux < 30) && (rainVal > 10)) {
      analogWrite(light, 69);
    } else {
      analogWrite(light, 5);
    }
  } else if (pirVal == LOW) {
    if (rainVal > 10) {
      tone(buzzer, 690);
      delay(250);
      tone(buzzer, 490);
      delay(250);
      tone(buzzer, 290);
      delay(250);
      tone(buzzer, 90);
      delay(250);
    } else {
      noTone(buzzer);
    }
    noTone(buzzer);
    digitalWrite(light, LOW);
  } else {
    noTone(buzzer);
    digitalWrite(light, LOW);
  }

  Serial.println("+++++++++++++++");
}
//RainSensor Value
int readSensor() {
  int sensorValue = analogRead(rainI);
  int outputValue = map(sensorValue, 0, 1023, 255, 0);
  return outputValue;
}

float tempLED(float temp) {
  //>18 | 22 |26 |30 | 34
  if (temp <= 18) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
    digitalWrite(led_5, LOW);
    Serial.println("pass 1");
  } else if (temp <= 22) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
    digitalWrite(led_5, LOW);
    Serial.println("pass 2");
  } else if (temp <= 26) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    digitalWrite(led_4, LOW);
    digitalWrite(led_5, LOW);
    Serial.println("pass 3");
  } else if (temp <= 30) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    digitalWrite(led_4, HIGH);
    digitalWrite(led_5, LOW);
    Serial.println("pass 4");
  } else if (temp <= 34) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    digitalWrite(led_4, HIGH);
    digitalWrite(led_5, HIGH);
    Serial.println("pass 5");
  }
}
