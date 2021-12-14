#define trigger1 D1
#define echo1 D2
#define Relay D3
#define trigger2 D4 
#define echo2 D5 

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Blynk Application Setup
char auth[] = "lLPjx72lGOkPjc9iA_KQfhG87KGoxMT6";
char ssid[] = "Test123";
char pass[] = "pakalupapito";

float time1 = 0, distance1 =0, time2 = 0, distance2 = 0, tinggi2 = 0;
int a, counter = 0;

void setup()
{
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
 pinMode(trigger1,OUTPUT);
 pinMode(echo1,INPUT);
 pinMode(Relay,OUTPUT);
 pinMode(trigger2, OUTPUT);
 pinMode(echo2,INPUT);
}
void measure_distance()
{
 digitalWrite(trigger1,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger1,LOW);
 delayMicroseconds(2);
 time1 = pulseIn(echo1,HIGH);
 distance1 = (time1 / 2) / 29.1;
}

void measure_distance2()
{
 digitalWrite(trigger2,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger2,LOW);
 delayMicroseconds(2);
 time2 = pulseIn(echo2,HIGH);
 distance2 = (time2 / 2) / 29.1;
 tinggi2 = 25 - distance2;
}
void loop()
{
 measure_distance();/////////// people
 measure_distance2(); //////////water kevek
 Serial.print("Hasil Sensor dispenser: ");
 Serial.print(distance1);
 Serial.println("cm");
 Serial.print("Hasil Sensor iot: ");
 Serial.print(distance2);
 Serial.println("cm");

 
 if(distance1 <= 5)
{
  if(a == 0){ 
//    myservo.write(0);
    digitalWrite(Relay, HIGH);
    delay(1000);
    digitalWrite(Relay, LOW);
    delay(20);
    Serial.println("dispense");
    a = 1;
    counter = counter++;
  }
  else
  {
    delay(3);
    }
}
else if(distance1 < 50)
{
    Serial.println("Presence");   
}
else if(distance1 < 100)
{
    a = 0;
    Serial.println("Too far");

}
else
{
  a = 0;
  Serial.println("Unknown");
}
  
  delay(250);          

 
 if(distance2 > 0 && distance2 < 5)
 {
   Blynk.virtualWrite(V2, 255);
   Blynk.virtualWrite(V1, 255);
   Blynk.virtualWrite(V0, 255);
   
 }
 
 else if(distance2 > 5 && distance2 < 7)
 {
   Blynk.virtualWrite(V2, 0);
   Blynk.virtualWrite(V1, 255);
   Blynk.virtualWrite(V0, 255);
 }

 else if(distance2 > 7 && distance2 < 12)
 {
   Blynk.virtualWrite(V2, 0);
   Blynk.virtualWrite(V1, 0);
   Blynk.virtualWrite(V0, 255);
 }
 
 else
 {
   Blynk.virtualWrite(V2, 0);
   Blynk.virtualWrite(V1, 0);
   Blynk.virtualWrite(V0, 0); 
   Blynk.notify("Water tank need to be refill");
 }
 
 Blynk.virtualWrite(V4, tinggi2);
 Blynk.virtualWrite(V3, distance2);
 Blynk.virtualWrite(V5, counter);
 delay(200);
 Blynk.run();
}
