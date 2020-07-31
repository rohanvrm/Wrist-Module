
#include <Wire.h>
#include <TFT.h>  
#include <SPI.h>

#include<SoftwareSerial.h>

#include "MAX30100_PulseOximeter.h"
#include "ClosedCube_MAX30205.h"

ClosedCube_MAX30205 max30205;


#define REPORTING_PERIOD_MS     1000


// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8


PulseOximeter pox;

uint32_t tsLastReport = 0;


SoftwareSerial bt(3,4); //  rx tx pin for bt modules 

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);



// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
    bt.println("Beat!");
}
void setup()
{
    Serial.begin(115200);
    bt.begin(9600);
     
    max30205.begin(0x48);

    
    
    Serial.print("Initializing pulse oximeter..");

    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        bt.println("FAILED");

        for(;;);
    } else {
        Serial.println("SUCCESS");
        bt.println("SUCCESS");

    }


    //initialize the library
   //TFTscreen.begin();

  // clear the screen with a black background
 // TFTscreen.background(0, 0, 0);
  //set the text size
  //TFTscreen.setTextSize(1);
  

    

    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);

    
}

void loop()
{
    // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
   if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      
        Serial.print("HR:");
        Serial.print(pox.getHeartRate());
        Serial.println("bpm ");
        bt.print("HR:");
        bt.print(pox.getHeartRate());
        bt.println("bpm ");
        
        Serial.print("SpO2: ");
        Serial.print(pox.getSpO2());
        Serial.println("%");
        bt.print("SpO2:");
        bt.print(pox.getSpO2());
        bt.println("%");
        
       
         
        Serial.print("Temp:");
        Serial.print(max30205.readTemperature());
        Serial.println("C");

        
        
        bt.print("Temp:");
        bt.print(max30205.readTemperature());
        bt.println("C");
       


         // set a random font color
  //TFTscreen.stroke(0, 255, 0);
  
  // print Hello, World! in the middle of the screen
  //TFTscreen.text("Hello, World!", 6, 57);
  



 
        tsLastReport = millis();
    }






    
}
