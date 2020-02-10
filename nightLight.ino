// Prototyping Studio: Night Light Assignment
// By: Olga Khvan and Brenda Penn
// This reads in values from a photocell resistor and determines the brightness of 3 RGB LED's. 
// The color of the LED's cycle through with each touch sensed by the force sensitive resistor.
// For the photocell resistor, referenced: https://learn.adafruit.com/photocells and https://learn.adafruit.com/photocells/arduino-code
// For the force sensitive resistor, referenced: https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr

 
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 3;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;    
int a = 190;

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int fsrPin = 3;     // the FSR and 10K pulldown are connected to a0
int fsrReading;
int count = 0; //0 - red, 1 - blue, 2 - green;

#define COMMON_ANODE

// 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 
        setColor(0, 0, 255);    
  
}
 
void loop(void) {
  
   // referenced: https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr
  fsrReading = analogRead(fsrPin);
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  if (fsrReading > 700) {
    count ++;
  }
  //cycle through 5 different colors depending on the count varible
  if (count % 5 == 0) {
      setColor(255, 0, 0);  
  } else if (count % 5 == 1) {
      setColor(0, 255, 0);    
  } else if (count % 5 == 2) {
      setColor(0, 0, 255);    
  } else if (count % 5 == 3) {
    setColor(0, 255, 255); 
  } else if (count % 5 == 4) {
    setColor(80, 0, 80); 
  }

  // referenced: https://learn.adafruit.com/photocells and https://learn.adafruit.com/photocells/arduino-code
  photocellReading = analogRead(photocellPin);  

  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  if (photocellReading >= 120) {
    LEDbrightness = 0;
  } else {
      photocellReading = a - photocellReading;
      LEDbrightness = map(photocellReading, 0, a, 0, 255);
  }
  
  analogWrite(LEDpin, LEDbrightness);
  delay(100);
}

//set the color for the RGB LEDs
void setColor(int red, int green, int blue) {
  #ifdef COMMON_ANODE
    red = 255 -red;
    green = 255 - green;
    blue = 255- blue;
  #endif
  analogWrite(9,red);
  analogWrite(10,green);
  analogWrite(11,blue);
}
