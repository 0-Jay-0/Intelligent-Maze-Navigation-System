#include <reg51.h>

// IR Sensor Definitions
sbit ir1 = P1^0; // Portside Sensor
sbit ir2 = P1^1; // Bow Sensor
sbit ir3 = P1^2; // Starboard Sensor

// Motor Control Definitions
sbit M1a = P3^1; // Motor 1: Input 1
sbit M1b = P3^0; // 				 Input 2
sbit M2a = P3^3; // Motor 2: Input 1
sbit M2b = P3^2; // 				 Input 2

//Global Variable Definitions
unsigned int i;

//Function Declarations
void delay(unsigned int n);
void movfwd();
void movrev();
void stall();
void turnport();
void turnstar();


void main()
{
    while(1)
		{			
			if(ir2)
			{
				movfwd();
			}
			else
			{
				stall();
				movrev();
				delay(1000);
				
				if(ir1)
				{
					turnport();
				}
				else if(ir3)
				{
					turnstar();					
				}
				
				delay(1000);
			}
			
			if (!ir2)
			{
				stall();
			}				
			
			if (!ir1)
			{
				turnstar();
			}
			
			if (!ir3)
			{
				turnport();
			}
			
			if(ir1 && ir2 && ir3)
			{
				movfwd();
			}
			
			delay(1);
		}
}


//Function Definitions
void delay(unsigned int n) //(nx1)ms Delay
{
	TMOD = 0x01;
	
	for(i = 0; i < n; i++)
	{
		TH0 = 0xF8;
		TL0 = 0xCC;
		
		TF0 = 0;
		TR0 = 1;
		while(!TF0);
		TR0 = 0;
		TF0 = 0;
	}
}

void movfwd() //Forward
{
	M1a = 1;
	M1b = 0;
	M2a = 1;
	M2b = 0;
}

void movrev() //Reverse
{
	M1a = 0;
	M1b = 1;
	M2a = 0;
	M2b = 1;
}

void turnport() //Turn Portside
{
	M1a = 0;
	M1b = 1;
	M2a = 1;
	M2b = 0;
}

void turnstar() //Turn Starboard
{
	M1a = 1;
	M1b = 0;
	M2a = 0;
	M2b = 1;
}

void stall() //Stop
{
	M1a = 0;
	M1b = 0;
	M2a = 0;
	M2b = 0;
}