char t;
int mode =0; 
const int trigPin = 2; // Ultrasonic
const int echoPin = 3;
long duration;
int distance;
int command1;
int command2;
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
void setup() {
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);  
pinMode(2,OUTPUT);   //left motors forward
pinMode(3,OUTPUT);   //left motors reverse
pinMode(4,OUTPUT);   //right motors forward
pinMode(7,OUTPUT);   //right motors reverse
pinMode(5,OUTPUT);//Enable right
pinMode(6,OUTPUT);   //Enable left
Serial.begin(9600);
while (!Serial);   // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
}
void loop() 
{
if(Serial.available()){
  t = Serial.read();
//  Serial.println(t);
}
if (t == 'X')
{
  mode=1-mode;
  Serial.print("Mode is :");
  Serial.println(mode);
}
if (mode == 0)
{
//Manual  
if(t == 'F') //move forward(all motors rotate in forward direction)
{           
//   Serial.println(t);
   Forward(80);
}
else if(t == 'B'){ //move reverse (all motors rotate in reverse direction)
//   Serial.println(t);
   Back(80);
}
 
else if(t == 'L') //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
{
//   Serial.println(t);
   Left(120);
}
 
else if(t == 'R')      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
{
//   Serial.println(t);
   Right(120);
}

 
else if(t == 'S')//STOP (all motors stop)
{      
//   Serial.println(t);
   Stop();
}
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  delay(1500);
  Serial.println();
}


else 
{
  //Automatic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print(distance);
  Serial.println();
  command1 = digitalRead(A4);
  command2 = digitalRead(A5);
  Serial.print(command1);
  Serial.print(command2);
  Serial.println();
 if(distance>20)
 {
 if(command1 ==1 && command2 ==1)
 {
  Forward(100);
  delay(100);
  Stop();
 }
  if(command1 ==1 && command2 ==0)
 {
  Right(140);
  delay(90);
  Stop();
 }
  if(command1 ==0 && command2 ==1)
 {
  Left(130);
  delay(90);
  Stop();
 }
  if(command1 ==0 && command2 ==0)
 {
  Stop();
 }
 }
 else
 {
  Serial.print("Object Detected");
  Serial.println();
  Stop();
 }
}
}
void Forward(int Speed)
{
  analogWrite(5,Speed);
  analogWrite(6,Speed+10);
  digitalWrite(2,HIGH);
  digitalWrite(7,HIGH);
}
void Back(int Speed)
{
  analogWrite(5,Speed);
  analogWrite(6,Speed);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH); 
}
void Left(int Speed)
{
  analogWrite(5,Speed);
  analogWrite(6,Speed);
  digitalWrite(7,HIGH);
}  
void Right(int Speed)
{
  analogWrite(5,Speed);
  analogWrite(6,Speed);
  digitalWrite(2,HIGH);
}
void Stop()  
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
}  
