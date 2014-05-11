/* Program

   A simple program created by the clixx.io generator now ready for 
   customisation.

*/

#include <stdio.h>
#include <string.h>

#include "clixxIO.hpp"
#include "seriallinehander-config.hpp"

class App : public clixxIOApp{

  public:

    void setup(){
        /* setup Event handler

         This is a built in handler that will get called on startup
         and provides for initialisation requirements.

        */
        Serial.begin();
        Serial.echo = 1;
        Serial.puts("Serial Line Handler Example running at 19200 baud\r\n");

    };

    void serialline(){
        /* SerialLine Event handler
         
         * This gets called when a line is received. We check it to
         * see if it matches "On" and then print out that this was
         * what was expected. In other cases, the received line is echoed
         * back on the terminal.
         
        */
        
        if (strncmp(Serial.lastline(),"On",BUFFSIZE_LINELEN) == 0)
        {
            Serial.puts("Turn On instruction was received\n\r");
        } else
        {
            Serial.puts("\r\nSerial line was :");
            Serial.puts(Serial.lastline());
            Serial.puts("\r\n");
        }

    };

};


// Main program Section. Simply setup an App class and let it run
int main(){
 
  App m;
  
  return m.run();

}

// Autogenerated interface between the event interface and application class
#include "seriallinehander-callbacks.cpp"
