#include <18F452.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use DELAY(clock=8000000)
#use SPI(FORCE_HW, BITS=8, stream=SPI_STREAM)
#use STANDARD_IO(a)
#use FAST_IO(b)

#define ONES PIN_A0
#define TENS PIN_A1
#define HUNDREDS PIN_A2
#define hundred 100
#define ten 10
#define one 1
#define delay 1

void set_number(int);
void set_one(int);
void set_ten(int);
void set_hundred(int);

int h = 0;
int _h = 0;
int t = 0;
int _t = 0;
int s = 0;
int i = 0;
short int deltaZero = 0;
short int deltaTen = 0;
short int deltaHun = 0;
short int busy = false;

void main()
{
	int x = 0;
	SET_TRIS_B(0x00);
	SETUP_SPI(SPI_SLAVE);

	for(;;)
	{
		if(SPI_DATA_IS_IN() && busy == false)
	   	{
		   	busy = true;
		   	deltaZero = 1;
	   		x = (int) SPI_READ();	   		
	   	}
	   	set_number(x);
	   	deltaZero = 0;
	}
}

void set_number(int number )
{	
	h = 0;
	_h = 0;
	t = 0;
	_t = 0;
	s = 0;
	i = 0;
	
	// Set hundreds value 
	if(number > 99)
	{
		h = (int)(number * 0.01);
	}
	
	// Set tens value 
	_h = (int)(h * 100);
	if( ( number - _h ) > 9 )
	{
		s = number - _h;
		t = (int)(s * 0.1);
		s = 0;
	}	
	
	// Set singles value
	_t = (int)(t * 10);
	s = (int)(number - (_t + _h));
	
	// Pass values to the displays 
	for ( i = 0;  i < 32;  i++ )
	{
		set_hundred(h);
		set_ten(t);
		set_one(s);
	}
	busy = false;
}	

void set_one( int num )
{
	output_high( ONES );
	switch( num )
	{
			case 0:
			if(deltaZero == 1){ output_b(0x40); }else{ output_b(0xC0); }			
			break;
			
			case 1:
			if(deltaZero == 1){ output_b(0x79); }else{ output_b(0xF9); }
			break;
			
			case 2:
			if(deltaZero == 1){ output_b(0x24); }else{ output_b(0xA4); }
			break;
			
			case 3:
			if(deltaZero == 1){ output_b(0x30); }else{ output_b(0xB0); }
			break;
			
			case 4:
			if(deltaZero == 1){ output_b(0x19); }else{ output_b(0x99); }
			break;
			
			case 5:
			if(deltaZero == 1){ output_b(0x12); }else{ output_b(0x92); }
			break;
			
			case 6:
			if(deltaZero == 1){ output_b(0x02); }else{ output_b(0x82); }
			break;
			
			case 7:
			if(deltaZero == 1){ output_b(0x78); }else{ output_b(0xF8); }
			break;
			
			case 8:
			if(deltaZero == 1){ output_b(0x00); }else{ output_b(0x80); }
			break;
			
			case 9:
			if(deltaZero == 1){ output_b(0x18); }else{ output_b(0x98); }
			break;
			
			default:
			if(deltaZero == 1){ output_b(0xFF); }else{ output_b(0x7F); }
			break;
	}	
	delay_ms(delay);	
	output_low(ONES);
}

void set_ten( int num )
{
	output_high(TENS);
	switch( num )
	{
			case 0:
			if(deltaTen == 1){ output_b(0x40); }else{ output_b(0xC0); }			
			break;
			
			case 1:
			if(deltaTen == 1){ output_b(0x79); }else{ output_b(0xF9); }
			break;
			
			case 2:
			if(deltaTen == 1){ output_b(0x24); }else{ output_b(0xA4); }
			break;
			
			case 3:
			if(deltaTen == 1){ output_b(0x30); }else{ output_b(0xB0);	}
			break;
			
			case 4:
			if(deltaTen == 1){ output_b(0x19); }else{ output_b(0x99); }
			break;
			
			case 5:
			if(deltaTen == 1){ output_b(0x12); }else{ output_b(0x92); }
			break;
			
			case 6:
			if(deltaTen == 1){ output_b(0x02); }else{ output_b(0x82); }
			break;
			
			case 7:
			if(deltaTen == 1){ output_b(0x78); }else{ output_b(0xF8); }
			break;
			
			case 8:
			if(deltaTen == 1){ output_b(0x00); }else{ output_b(0x80); }
			break;
			
			case 9:
			if(deltaTen == 1){ output_b(0x18); }else{ output_b(0x98); }
			break;
			
			default:
			if(deltaTen == 1){ output_b(0xFF); }else{ output_b(0x7F); }
			break;
	}	
	delay_ms(delay);	
	output_low(TENS);
}

void set_hundred( int num )
{
	output_high(HUNDREDS);
	switch( num )
	{
			case 0:
			if(deltaHun == 1){ output_b(0x40); }else{ output_b(0xC0); }			
			break;
			
			case 1:
			if(deltaHun == 1){ output_b(0x79); }else{ output_b(0xF9); }
			break;
			
			case 2:
			if(deltaHun == 1){ output_b(0x24); }else{ output_b(0xA4); }
			break;
			
			case 3:
			if(deltaHun == 1){ output_b(0x30); }else{ output_b(0xB0);	}
			break;
			
			case 4:
			if(deltaHun == 1){ output_b(0x19); }else{ output_b(0x99); }
			break;
			
			case 5:
			if(deltaHun == 1){ output_b(0x12); }else{ output_b(0x92); }
			break;
			
			case 6:
			if(deltaHun == 1){ output_b(0x02); }else{ output_b(0x82); }
			break;
			
			case 7:
			if(deltaHun == 1){ output_b(0x78); }else{ output_b(0xF8); }
			break;
			
			case 8:
			if(deltaHun == 1){ output_b(0x00); }else{ output_b(0x80); }
			break;
			
			case 9:
			if(deltaHun == 1){ output_b(0x18); }else{ output_b(0x98); }
			break;
			
			default:
			if(deltaHun == 1){ output_b(0xFF); }else{ output_b(0x7F); }
			break;
	}	
	delay_ms(delay);
	output_low(HUNDREDS);
}

