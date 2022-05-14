#include <Arduino.h>
#include <SPI.h>

#define NUMPIXEL 8
#define COLOURBYTES 192

uint8_t displayMem[COLOURBYTES];
uint8_t colCorrect[6];
uint8_t SPIPos = 0;

void setup() {
  // set prescaler to 128 -> TCNT2 freq = 125KHz
  TCCR2B |= ((1<<CS22)|(1<<CS20)|(0<<CS21));
  //TCCR2B &= ~((1<<CS21));   

  TCCR2A |= ((0<<WGM21) | (0<<WGM20));   // Use normal mode
  ASSR |= (1<<AS2);       // Use internal clock - external clock not used in Arduino
  TIMSK2 |= ((1<<TOIE2) | (0<<OCIE2B));   //Timer2 Overflow Interrupt Enable
  TCNT2 = 0xff;

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);  
  SPI.attachInterrupt();
}



//SPI Intterupt routine
ISR (SPI_STC_vect)
{
  if (SPIPos < COLOURBYTES) {
    displayMem[SPIPos++] = SPDR;
  } else {
    SPIPos = 0;
  }
}

ISR(TIMER2_OVF_vect)          //Timer2  Service 
{ 
 // ISR fires every 256-TCNT2 ticks
 // so if TCNT2 = 100, ISR fires every 156 ticks
 // prescaler = 128 so ISR fires every 16MHz / 128 = 125KHz
 // 125KHz / 156 = 801.282Hz / 8 rows = 100.16Hz refresh rate
 // if TCNT2 = 61, ISR fires every 256 - 61 = 195 ticks
 // 125KHz / 195 = 641.026Hz / 8 rows = 80.128Hz refresh rate
  //  TCNT2 = 100;
  TCNT2 = 0;
  /*set lines here
  close_all_lines;  
  Colorduino.run();
  Colorduino.open_line(Colorduino.line);
  if (++Colorduino.line > 7) Colorduino.line = 0;*/
}

int main(){
  while(true){

  }
}
  