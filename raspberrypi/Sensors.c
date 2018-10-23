#include<wiringPi.h>
#include<stdio.h>
#include<stdlib.h>
#include <pcf8591.h>
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
#define HIGH_TIME 32
int pinNumber=3;
uint32 databuf;


#define Address 0x48
#define BASE 64
#define A0 BASE+0
#define A1 BASE+1
#define A2 BASE+2
#define A3 BASE+3
float  value0,value1;

uint8 readSensorData(void)
{
	uint8 crc;
	uint8 i;

	pinMode(pinNumber,OUTPUT);
	digitalWrite(pinNumber,1);
	delayMicroseconds(4);
	digitalWrite(pinNumber,0);
	delay(25);
	digitalWrite(pinNumber,1);
	delayMicroseconds(60);
	pinMode(pinNumber,INPUT);
	pullUpDnControl(pinNumber,PUD_UP);

	if(digitalRead(pinNumber)==0)
	{
		while(!digitalRead(pinNumber));
		delayMicroseconds(80);
		for(i=0;i<32;i++)
		{
			while(digitalRead(pinNumber));
			while(!digitalRead(pinNumber));
			delayMicroseconds(HIGH_TIME);
			databuf*=2;
			if(digitalRead(pinNumber)==1)
			{
				databuf++;
			}
		}
		for(i=0;i<8;i++)
		{
			while(digitalRead(pinNumber));
			while(!digitalRead(pinNumber));
			delayMicroseconds(HIGH_TIME);
			crc*=2;
			if(digitalRead(pinNumber)==1)
			{
				crc++;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
	int main(void)
	{
		if(-1==wiringPiSetup())
		{
			printf("Setup wiringPi failed!");
			return 1;
		}
		/*****mq2,mq135*****/
		pcf8591Setup(BASE,Address);
		if(value0>50)
		value0=analogRead(A0)*100/255;
		else{
			value0=0;}
		value1=analogRead(A1)*0.586+50;

		/*****dht11*****/
		pinMode(pinNumber,OUTPUT);
		digitalWrite(pinNumber,1);
		//while(1)
		//{
			pinMode(pinNumber,OUTPUT);
			digitalWrite(pinNumber,1);
			delay(3000);
		if(readSensorData())
		{
			printf("OK!\n");
			//printf("RH:%d.%d\n",(databuf>>24)&0xff,(databuf>>16)&0xff);
			//printf("TMP:%d.%d\n",(databuf>>8)&0xff,databuf&0xff);
			//databuf=0;
			FILE *fp=fopen("data","w");
			fprintf(fp,"%d.%d\n%d.%d\n%.2f\n%.2f",(databuf>>24)&0xff,(databuf>>16)&0xff,(databuf>>8)&0xff,databuf&0xff,value0,value1);
			fclose(fp);
			databuf=0;
		}
		else
		{
			printf("Error!\n");
			databuf=0;
		}
		
		return 0;
	}
