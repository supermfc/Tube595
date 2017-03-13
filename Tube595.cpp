/*
 *  Tube display utilities for 74HC595 IC  
 *  Code by DingBing in jiaozuo city henan province China
	My QQ：396364218 and i love mcu & arduino.

 *  This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See Github project https://github.com/supermfc/Tube595 for latest
 */
#ifndef TUBE595_cpp
#define TUBE595_cpp

#include "Tube595.h"

unsigned char Tube595::LED_MODEL[17] = 
    { 
    // 0    1     2   3    4    5    6    7    8     9   A    B    C    D    E    F    - 
      0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0x8E,0xbf};

unsigned char Tube595::LedData[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

Tube595::Tube595(int dataPin,int sclkPin,int rclkPin)
{
	DIO = dataPin;
	SCLK = sclkPin;
	RCLK = rclkPin;
	
	pinMode(SCLK,OUTPUT);
	pinMode(RCLK,OUTPUT);
	pinMode(DIO,OUTPUT); 
}

void Tube595::setLetter(int place,char letter)
{
	if( (letter >= 'A') & ( letter <= 'F'))
		LedData[place] = LED_MODEL[letter-55];
	if( letter == '-')
		LedData[place] = LED_MODEL[16];
}

void Tube595::setDigital(int place,int digital)
{
	Tube595::LedData[place] = Tube595::LED_MODEL[digital];
}


// display a int number
void Tube595::displayInt(int num)
{
	char string[9]={0};
	sprintf(string,"%8d",num);
  
	for(int i = 7; i >=0; i--) 
	{
		switch(string[i])
		{
			case ' ':
				break;
			case '-':
				LedData[7-i] = LED_MODEL[16];
				break;
			default:
				LedData[7-i] = LED_MODEL[string[i]-'0'];
       // LedData[7-i] = LED_MODEL[1];
				break;       
		}
	}
	update();
}

//prec 小数位数
void Tube595::displayFloat(float number,int prec)
{
	char str[10]={0};
	int j = 9;
	int point = 0;
	dtostrf(number,8,prec,str);

	while(str[j]==0)
		j--;

	for(int i = 7; i >= 0; i--) 
	{
    
		switch(str[j])
		{
			case ' ':
				break;
			case '-':
				LedData[7-i] = LED_MODEL[16];
				break;
			case '.':
				LedData[7-i] &= 0x7F;
				i++;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				LedData[7-i]  &=  LED_MODEL[str[j]-'0']  ;
				//LedData[7-i] = LED_MODEL[3];
				break;     
     
		}
			// LedData[7-i] = LED_MODEL[i];
		j--;
   
	}

	update();

}

void Tube595::setNoPoint(int place)
{
	LedData[place] |= 0x80;
}

void Tube595::setPoint(int place)
{
	LedData[place] &= 0x7F;
}

void Tube595::closeDisplay()
{
	for(int i = 0; i < 8;i ++)
		LedData[i] = 0xFF;
	
	update();
}
void Tube595::update()
{
	for(int i = 0 ; i < 8; i++)
	{
	shiftOut(DIO,SCLK,MSBFIRST,LedData[i]);
	shiftOut(DIO,SCLK,MSBFIRST,1<<i);
    digitalWrite(RCLK,LOW);
    digitalWrite(RCLK,HIGH);
	}
}




#endif
