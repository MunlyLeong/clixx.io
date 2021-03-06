/* Program

   A simple program created by the clixx.io generator now ready for 
   customisation.

*/

#include "clixxIO.hpp"
#include "remotebutton-config.hpp"

#define F_CPU 8000000UL
#include <util/delay.h>
#include <core_AVR/iohelp.h>

clixxIO_Button mybutton(BUTTON1_CONFIG);

class App : public clixxIOApp{

  public:

    void setup(){
        /* setup Event handler
         * 
         * This is a built in handler that will get called on startup
         * and provides for initialisation requirements.
         * 
         */

        Switch1.assignPin(ADC2);
        
        IoT.begin();

        Debug.puts("Application in setup event");

        IoT.beginPublishing("SmallDevice/Button");
        
    };

    void loop(){
        /* 
         * Loop Event handler - This gets called repeatedly.
         */
        if (mybutton.pressed()){

            Debug.puts("Button Pressed");

            IoT.publish("On");

        } else {

            IoT.publish("Off");
            
        }

        _delay_ms(333); 
    };

};

// Main program Section. Simply setup an App class and let it run
int main(){
 
  App m;

  return m.run();

}

// Autogenerated interface between the event interface and application class
#include "remotebutton-callbacks.cpp"
