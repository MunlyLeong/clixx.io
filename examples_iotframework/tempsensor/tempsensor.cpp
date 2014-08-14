/* Program

   A simple program created by the clixx.io generator now ready for 
   customisation.

*/

#include <stdio.h>
#include "clixxIO.hpp"
#include "tempsensor-config.hpp"

#include "clixxIO_Temp-LM335A.h"

LM335A InsideTemp(0); //pass the analog input pin number

class App : public clixxIOApp{

  public:

    void setup(){
        /* setup Event handler

         This is a built in handler that will get called on startup
         and provides for initialisation requirements.

        */
        Debug.puts("Application in Startup event");
        Serial.begin(115200);
        Serial.println("starting");

    };

    void timer(){
        /* timer Event handler
         
         This will get called automatically by the timer.
         
        */
        Debug.puts("Timer Callback");
    }

    void loop() {

        delay(3000);
        //user must call ReadTemp before any valid temp data is available
        InsideTemp.ReadTemp();  
        Serial.print("Fahrenheit: ");
        
        //functions to get the temperature in various unitsfs
        Serial.println(InsideTemp.Fahrenheit());
        Serial.print("Celsius: ");
        Serial.println(InsideTemp.Celsius());
        Serial.print("Kelvin: ");
        Serial.println(InsideTemp.Kelvin());
    };

};

// Main program Section. Simply setup an App class and let it run
int main(){
 
  App m;
  
  return m.run();

}

// Autogenerated interface between the event interface and application class
#include "tempsensor-callbacks.cpp"