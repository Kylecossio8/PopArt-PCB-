#include <Adafruit_NeoPixel.h>
#include "frames.h"
#include <Bounce2.h>

Bounce2::Button button = Bounce2::Button();

#define BUTTON_PIN 1

Adafruit_NeoPixel strip(24, 0);

int switchVal = 0;

int colors [4][3]{
  {0,0,0},
  {0,0,255},
  {255,0,0},
  {255,165,0}
};

int whichFrame = 0;

//timer variables
int sTime;
int eTime;
int interval;


void setup() {

  //mode = 0;
  button.attach(BUTTON_PIN, INPUT);
  
  button.interval(10); //debounce interval in ms
 
  sTime = millis();
  interval = 1500;
  
  strip.begin();
  strip.clear();
  strip.setBrightness(50);
}

void loop() {

   if (button.rose()){
    switchVal = switchVal +1;
   
   }

  switch(switchVal){
    case 0: off(); break;
    case 1: on(); break;
    case 2: simple(); break;
    case 3: mapped();  break;
  }
    
  switchVal = (switchVal + 1) % 4;
}

void off(){
  strip.begin();
  strip.clear();
  strip.show();
}

void on(){
  strip.begin();
  strip.clear();

  strip.setPixelColor(0, 255,0,0);
  strip.setPixelColor(1, 255,0,0);
  strip.setPixelColor(17, 255,0,0);
  strip.setPixelColor(18, 255,0,0);
  strip.setPixelColor(21, 255,0,0);
  strip.setPixelColor(22, 255,0,0);

  strip.show();
}
void simple(){

  for (int i = 0; i < strip.numPixels(); i++) {
    int whichColor = pixelMap[i];
    int red = colors[whichColor][0];
    int green = colors[whichColor][1];
    int blue = colors [whichColor][2];
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
  }



void mapped(){
  for (int i = 0; i < strip.numPixels(); i++) {
    int pixAddress = pixelMap[i];
    int whichColor = animation[whichFrame][i];
    int blue = colors[whichColor][0];
    int red = colors[whichColor][1];
    int orange = colors[whichColor][2];
    
    if(pixAddress != -1){
      strip.setPixelColor(pixAddress, blue,red,orange);
    }
    }
  strip.show();
  delay(500);
  whichFrame = (whichFrame + 1) % 5;
}
