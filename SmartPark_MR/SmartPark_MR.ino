  //IR sensors for parking spaces
 int parkingOneIR = 13;
 int parkingTwoIR = 12;
 int parkingThreeIR = 11;

 //LED for  occupied parking spaces
 int parkingOneLedOcc = 10;
 int parkingTwoLedOcc = 9;
 int parkingThreeLedOcc = 7;

 //LED for non-occupied parking spaces
 int parkingOneLedNO = 6;
 int parkingTwoLedNO = 5;
 int parkingThreeLedNO = 4;

 //LED for full parking indicator
 int parkingFullInd = 3;

 //buzzer indicator for full parking
 int parkingBuzzer = 2;

void setup() {
 //PIN MODE
 pinMode(parkingOneIR, INPUT);
 pinMode(parkingTwoIR, INPUT);
 pinMode(parkingThreeIR, INPUT);

 pinMode(parkingOneLedOcc, OUTPUT);
 pinMode(parkingTwoLedOcc, OUTPUT);
 pinMode(parkingThreeLedOcc, OUTPUT);

 pinMode(parkingOneLedNO, OUTPUT);
 pinMode(parkingTwoLedNO, OUTPUT);
 pinMode(parkingThreeLedNO, OUTPUT);

 pinMode(parkingFullInd, OUTPUT);

 pinMode(parkingBuzzer, OUTPUT);

 Serial.begin(9600); 

}

void loop() {
  // IR read
  //int serial

  int sensorStatusOne = digitalRead(parkingOneIR);
  int sensorStatusTwo = digitalRead(parkingTwoIR);
  int sensorStatusThree = digitalRead(parkingThreeIR);

  if(sensorStatusOne == LOW){
    digitalWrite(parkingOneLedOcc, HIGH);
    digitalWrite(parkingOneLedNO, LOW);
    Serial.println("NOTHING HERE");
  }else{
    digitalWrite(parkingOneLedOcc, LOW);
    digitalWrite(parkingOneLedNO, HIGH);
    Serial.println("PARKED");
  }

  if(sensorStatusTwo == LOW){
    digitalWrite(parkingTwoLedOcc, HIGH);
    digitalWrite(parkingTwoLedNO, LOW);
    Serial.println("It works!");
  }else{
    digitalWrite(parkingTwoLedOcc, LOW);
    digitalWrite(parkingTwoLedNO, HIGH);
    Serial.println("It works!");
  }

  if(sensorStatusThree == LOW){
    digitalWrite(parkingThreeLedOcc, HIGH);
    digitalWrite(parkingThreeLedNO, LOW);
    Serial.println("It works!");
  }else{
    digitalWrite(parkingThreeLedOcc, LOW);
    digitalWrite(parkingThreeLedNO, HIGH);
    Serial.println("It works!");
  }

  if((sensorStatusOne == LOW) && (sensorStatusTwo ==LOW) && (sensorStatusThree == LOW)){
    digitalWrite(parkingFullInd, HIGH);
    delay(5);
    digitalWrite(parkingFullInd, LOW);

    tone(parkingBuzzer, 690);
    delay(200);
    noTone(parkingBuzzer);
    delay(100);
  }

}



