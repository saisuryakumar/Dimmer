#include<reg51.h>

sbit Out = P2^0;
sbit Inc = P1^0;
sbit Dec = P1^1;


sbit Led1 = P2^1;
sbit Led2 = P2^2;
sbit Led3 = P2^3;
sbit Led4 = P2^4;
sbit Led5 = P2^5;

void cct_init(void);
void InitINT(void);

int Step =3;

// Main function
int main(void)
{
	int i;
  cct_init();
	InitINT();
	Step = 0;
	
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x01;    // Set timer0 in mode 1 = 16bit mode
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
  while(1)                
   {				 
		 	 
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
			 
			if(Inc == 0 && Step <5)
			{
					 Step = Step + 1;
					 for(i=0;i<50;i++);
			}
			if(Dec == 0 && Step >0)
			{
					 Step = Step - 1;
					 for(i=0;i<50;i++);
			}
			
				 
	 }
}

// Circuit Initialize function
void cct_init(void)
{
	P0 = 0xFF;   
	P1 = 0xFF;   
	P2 = 0xFF;   
	P3 = 0xFF;  
}

// External INT0 pin interrupt init function
void InitINT(void)
{
	IT0 = 1;      //Edge triggered interrupt mode (Neg Edge)
	//IT1 = 1;
	EX0 = 1;  	//Enable external interrupt INT0
	//EX1 = 1;
	EA  = 1;      //Enable global interrupts
}


// INT0 ISR
void Zero_Cross_Intr(void) interrupt 0    
{
	TR0 = 0;
	
	TH0  = 0xFF - ((Step*1900)>>8)&0xFF;	// Load timer0 registers with 
	TL0  = 0xFF - (Step*1900)&0xFF;		// delay value		

	TR0 = 1;         // Start Timer 0
	Out = 0xFF;
	while(!TF0);  // Wait for timeup
	TF0 =0;
	
	         // Done
	Out = 0x00;
}
