#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "nRF24L01.h"
#include <RF24_config.h>
#define echoPin 5
#define trigPin 6 
const int AOUTpin = 0;
float distance1,duration;
int value1;
RF24 radio(7,8);
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL , 0xF0F0F0F0E4LL };

void setup(void)
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_1MBPS);
    radio.setRetries(15,15);
    radio.openWritingPipe(pipes[1]);
    radio.stopListening();
}

void loop(void)
{
    radio.stopListening();
    value1 = analogRead(AOUTpin);
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(100); 
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance1 = (duration/58.2);
    
    Serial.println(distance1);
    Serial.println(value1);
    radio.write( &distance1, sizeof(float) );
    radio.write( &value1, sizeof(int) );
    radio.startListening();
    delay(2000);
}
