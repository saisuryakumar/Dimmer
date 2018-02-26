#include<reg51.h>

sbit Out = P2^0;
sbit In = P1^0;


sbit Led1 = P2^1;
sbit Led2 = P2^2;
sbit Led3 = P2^3;
sbit Led4 = P2^4;
sbit Led5 = P2^5;

void cct_init(void);
void delay_usec(unsigned int);
void InitINT(void);

unsigned char TimeUp = 0;
int Step =0;

// Main function
int main(void)
{
	
  cct_init();
	InitINT();
	
  while(1)                
   {				 
		 
		 if(In == 1 && Step >0)
		 {
			 Out = 0xFF;
			 delay_usec(1900*Step);
			 
		 }
		 else 
			 Out = 0x00;
		 
		 switch(Step)
		 {
			 case 0:
					Led1 = 0x00;
					Led2 = 0x00;
					Led3 = 0x00;
					Led4 = 0x00;
					Led5 = 0x00;
			 break;
			 
			 case 1:
					Led1 = 0xFF;
					Led2 = 0x00;
					Led3 = 0x00;
					Led4 = 0x00;
					Led5 = 0x00;
			 break;
			 
			 case 2:
					Led1 = 0xFF;
					Led2 = 0xFF;
					Led3 = 0x00;
					Led4 = 0x00;
					Led5 = 0x00;
			 break;
			 
			 case 3:
					Led1 = 0xFF;
					Led2 = 0xFF;
					Led3 = 0xFF;
					Led4 = 0x00;
					Led5 = 0x00;
			 break;
			 
			 case 4:
					Led1 = 0xFF;
					Led2 = 0xFF;
					Led3 = 0xFF;
					Led4 = 0xFF;
					Led5 = 0x00;
			 break;
			 
			 case 5:
					Led1 = 0xFF;
					Led2 = 0xFF;
					Led3 = 0xFF;
					Led4 = 0xFF;
					Led5 = 0xFF;
			 break;
		 }
				 
	 }
}

// Circuit Initialize function
void cct_init(void)
{
	P0 = 0xFF;   
	P1 = 0xFF;   
	P2 = 0x00;   
	P3 = 0xFF;  
}

// Delay function, it generates delay in micro seconds
void delay_usec(unsigned int d)   // d can have a value from 0 to 65535 only.
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x01;    // Set timer0 in mode 1 = 16bit mode
	
	TH0  = 0xFF - (d>>8)&0xFF;	// Load timer0 registers with 
	TL0  = 0xFF - d&0xFF;		// delay value							   
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TimeUp = 0;      // When timer expires then this variable will become 1

	TR0 = 1;         // Start Timer 0

	while(!TimeUp);  // Wait for timeup

	TR0 = 0;         // Done
}

// Timer0 ISR function
void Timer0_ISR (void) interrupt 1   // It is called after every 250usec
{
	TimeUp = 1;  // Make TimeUp variable 1 to indicate timer0 overflow
	TF0 = 0;     // Clear the interrupt flag
}


// External INT0 pin interrupt init function
void InitINT(void)
{
	IT0 = 1;      //Edge triggered interrupt mode (Neg Edge)
	IT1 = 1;
	EX0 = 1;  	//Enable external interrupt INT0
	EX1 = 1;
	EA  = 1;      //Enable global interrupts
}


// INT0 ISR
void Inc_isr(void) interrupt 0     
{
	Step = Step + 1;
	if(Step >=5)
		Step = 5;
} 
void Dec_isr(void) interrupt 2    
{
	Step = Step - 1;
	if(Step <=0)
		Step = 0;	
} 
