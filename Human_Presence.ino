#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(9, 10);

int a=100;
int b;
 
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);     // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(7, INPUT);      // PIR
  pinMode(3, OUTPUT);     // Buzzer
  pinMode(A1, INPUT);     // LDR
  pinMode(5, OUTPUT);     // LED
}

void loop()
{
 delay(2000);
 a=digitalRead(7);
 Serial.println(a);
 b=analogRead(A1);
 Serial.println(b);
 
if(a==1&& b>600)
 { 
  digitalWrite(5,HIGH);
  digitalWrite(3,HIGH);
  delay(500);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  SendMessage();
 }

if(a==1&& b<600)
 {
  digitalWrite(5,HIGH);
  digitalWrite(3,LOW);
  delay(500);
  digitalWrite(5,LOW);
  SendMessage();
 }
      
 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}
 void SendMessage()
 {
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918921747353\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.print("Tresspassing!!!");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(10000);
 }
