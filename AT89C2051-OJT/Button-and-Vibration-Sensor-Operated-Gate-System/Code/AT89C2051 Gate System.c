#include<stdio.h>
#include<reg51.h>
#include <intrins.h>

sbit LED_1 = P1^0;	// OPEN GATE LED Indicator
sbit LED_2 = P1^1;	// CLOSE GATE LED Indicator
sbit LED_3 = P1^2;	// STOP GATE LED Indicator
sbit LED_4 = P1^3;	// LOCK GATE LED Indicator (RED)
sbit button_1 = P3^2;	// OPEN GATE BTN
sbit button_2 = P3^3;	// CLOSE GATE BTN
sbit button_3 = P3^4;	// STOP GATE BTN
sbit button_4 = P3^5;	// LOCK GATE BTN
sbit servo_pin = P3^0;	// Servo as a gate
sbit sensor = P3^1;	// VIBRATION Sensor

void init(void);
void delay(int sec);

void init(void)
{
  P1 = 0x00;
  P3 = 0x00;
  button_1 = 1;
  button_2 = 1;
  button_3 = 1;
  button_4 = 1;
  sensor = 1;
}

void delay(int sec)
{ 
	int i;
	for(i = 0; i < sec; i++);
}

void servo_angle(unsigned int deg)
{
  while(deg--)
  {
    _nop_();
  }
}

void main ( void )
{
	init();
	while(1)
	{
		servo_pin = 0;
		
		// If "OPEN" button is pressed AND "LOCK" is not pressed AND sensor is in HIGH state
		if(button_1 == 0 && button_4 != 0 && sensor != 0)	// OPEN
		{
			// ON LED 1
			LED_1 = 1;
			LED_2 = 0;
			LED_3 = 0;
			LED_4 = 0;
			
			//Rotate servo to OPEN
			servo_pin=1;	
			servo_angle(95);
		}
		// If "CLOSE" button is pressed AND "LOCK" is not pressed AND sensor is in HIGH state
		if (button_2 == 0 && button_4 != 0 && sensor != 0){	// CLOSE
			// ON LED 2
			LED_2 = 1;
			LED_1 = 0;
			LED_3 = 0;
			LED_4 = 0;
			//Rotate servo to CLOSE
			servo_pin = 1;
			servo_angle(50);
		} 
		if (button_3 == 0 && button_4 != 0){	// STOP
			LED_3 = 1;
			LED_1 = 0;
			LED_2 = 0;
			LED_4 = 0;	
		}
		
		if (button_4 == 0){	// LOCK both OPENING and CLOSING OF GATE
			// ON red LED indicating the locking of gate functionalities
			LED_4 = 1;
			LED_1 = 0;
			LED_2 = 0;
			LED_3 = 0;		
			// No button interaction
		}
		
		if (button_4 == 1){	// LOCK both OPENING and CLOSING OF GATE
			// ON red LED indicating the locking of gate functionalities
			LED_4 = 0;	
			// No button interaction
		}
	}
} 
