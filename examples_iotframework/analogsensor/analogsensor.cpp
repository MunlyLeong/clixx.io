/* Program

   A simple program created by the clixx.io generator now ready for 
   customisation.

*/

#include <stdio.h>
#include "clixxIO.hpp"
#include "analogsensor-config.hpp"

#define F_CPU 8000000UL
#include <util/delay.h>
#include <core_AVR/iohelp.h>

class App : public clixxIOApp{

  public:

    void setup(){
        /* setup Event handler

         This is a built in handler that will get called on startup
         and provides for initialisation requirements.

        */
        adcInit(ADC3);
        
        IoT.begin();
        IoT.beginPublishing("SmallDevice/AnalogSensor");

    };

    void loop(){
        /* Loop Event handler
         
         This gets called repeatedly.
         
        */
        int i = adcRead(ADC3);

        IoT.publish(i);

        _delay_ms(333); 
    };

};


// Main program Section. Simply setup an App class and let it run
int main(){
 
  App m;
  
  return m.run();

}

// Autogenerated interface between the event interface and application class
#include "analogsensor-callbacks.cpp"
