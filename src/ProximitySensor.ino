SYSTEM_THREAD(ENABLED);
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "oled-wing-adafruit.h"

VCNL4040 vc;
OledWingAdafruit oled = oledSetup();
void setup() {
  // Set up Output Pins
  pinMode(D8, OUTPUT); // RED LED
  pinMode(D7, OUTPUT); // YELLOW LED
  pinMode(D6, OUTPUT); // GREEN LED

  // Start I2C Connection
  Wire.begin();
}

void loop() {
  oled.loop();

  // Turn off all LEDs
  digitalWrite(D8, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D6, LOW);

  // Turns on each LED based on proximity
  if(vc.getProximity() < 100) digitalWrite(D8, HIGH); 
  if(vc.getProximity() < 1000) digitalWrite(D7, HIGH);
  else digitalWrite(D6, HIGH)

  if(oled.pressedA()){
    // Switch Modes
    vc.powerOnProximity(); 
    vc.powerOffAmbient(); 

    oled = oledSetup(); // Reset OLED

    oled.println("proxVal: " + vc.getProximity())
    oled.display();
  }
    if(oled.pressedB()){
    // Switch Modes
    vc.powerOffProximity(); 
    vc.powerOnAmbient(); 

    oled = oledSetup(); // Reset OLED

    oled.println("lightVal: " + vc.getAmbient())
    oled.display();
  }
  if (display.pressedC()){
    oled = oledSetup(); // Reset OLED
    oled.println("I2CAddress: " + vc.getID())
    oled.display();
  }
}

oled oledSetup(){
  oled.setup(); // Initialize OLED
  oled.clearDisplay(); // Clear OLED Screen
  oled.setCursor(0,0); // Reset cursor
  oled.setTextSize(0); // Set text size to 0
	oled.display(); // Update OLED
}