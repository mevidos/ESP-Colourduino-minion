#include <Arduino.h>
#include "Wire.h"
#include "Colorduino.h"

#define NUMPIXEL 8
#define COLOURBYTES 192


uint8_t update = 0;

void receiveEvent(int howMany) {
      if(howMany >= 64){
      byte colour = Wire.read();
      update++;
        for(byte x = 0; x <64; x++) {
          switch (colour)
          {
          case 'R':
            Colorduino.SetRed(x,Wire.read());
            break;
          case 'G':
            Colorduino.SetGreen(x,Wire.read());
            break;
          case 'B':
            Colorduino.SetBlue(x,Wire.read());
            break;
          }
       }
      if(update >= 2) {
        Colorduino.FlipPage();
      }
  }
}


int main() {
  //Serial.begin(500000);
  Wire.begin(0x65);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  Serial.begin(115200);
  Colorduino.Init();
  unsigned char whiteBalVal[3] = {36,63,63};
  Colorduino.SetWhiteBal(whiteBalVal);
  Colorduino.ColorFill(255,0,0);
  Colorduino.SetTimerCounter(0);
  Wire.onReceive(receiveEvent);
  while(true){

  }

}

  
