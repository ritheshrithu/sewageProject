#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



float distance1,distance2,distance3;
int value1,value2,value3;
int sp = 5;
RF24 radio(7,8);
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL , 0xF0F0F0F0E4LL };

void setup(void) 
{
Serial.begin(115200);
radio.begin();
radio.setPALevel(RF24_PA_MAX);
radio.setDataRate(RF24_1MBPS);
radio.openReadingPipe(1, pipes[1]);
radio.startListening();
radio.openReadingPipe(2, pipes[2]);
radio.startListening();
radio.openReadingPipe(3, pipes[3]);
radio.startListening();
}

void loop(void)
{

if ( radio.available() )
{
radio.read(&distance1, sizeof(distance1));
radio.read(&distance2, sizeof(distance2));
radio.read(&distance3, sizeof(distance3));
radio.read(&value1, sizeof(value1));

Serial.print("SEWER LEVEL 1 ");
Serial.print(distance1);
Serial.println();
Serial.print("GAS LEVEL 1   ");
Serial.print(value1);
Serial.println();
Serial.println();

Serial.print("SEWER LEVEL 1 ");
Serial.print(distance1);
Serial.println();
Serial.print("GAS LEVEL 2   ");
Serial.print(value2);
Serial.println();
Serial.println();

Serial.print("SEWER LEVEL 1 ");
Serial.print(distance3);
Serial.println();
Serial.print("GAS LEVEL 3   ");
Serial.print(value3);
Serial.println();
Serial.println();
Serial.println();
delay(3000);
if(distance1 !=distance2)
{
if(distance1 < sp)
{
  Serial.println("BLOCK PRESENT INBETWEEN 1 AND 2");
}

if(distance2 < sp)
{
  Serial.println("BLOCK PRESENT INBETWEEN 2 AND 3");
}

if(distance3 < sp)
{
  Serial.println("BLOCK PRESENT INBETWEEN 3 AND 4");
}
}
}
}
