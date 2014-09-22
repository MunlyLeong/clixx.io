/* serial-hbridge
 * 
 * This program provides a serial port and a command-line-interface for
 * controlling a h-bridge motor controller.
 * 
 * It's designed for the Attiny85. Simply connect the H-Bridge to the
 * Digital-1 Port.
 * 
*/

#include "clixxIO.hpp"
#include "serial-hbridge-config.hpp"

class App : public clixxIOApp{

  public:

    void setup()
    {
        /* setup Event handler */

        Serial.begin();
        Serial.puts("\r\nH-Bridge Motor Controller\r\n");
        Serial.puts("Commands are: 'f'=Forward,'r'=Reverse,'b'=Brake,'0'=Off\r\n");
        Serial.echo = 1;
        
        pin_fwd.configure(PB4,OUTPUT);
        pin_rvs.configure(PB3,OUTPUT);

    };

    void serialline()
    {
        /* SerialLine Event handler - gets called when a line is received. */
        char *cptr = (char *) Serial.lastline();
        char c = *cptr;
        
        if (c == 'f')
        {
            Serial.puts("Forward\r\n");
            pin_fwd.setval(1);
            pin_rvs.setval(0);
        }
        else if (c == 'r')
        {
            Serial.puts("Reverse\r\n");
            pin_fwd.setval(0);
            pin_rvs.setval(1);
        }
        else if (c == '0')
        {
            Serial.puts("Turned Off\r\n");
            pin_fwd.setval(0);
            pin_rvs.setval(0);
        } 
        else if (c == 'b')
        {
            Serial.puts("Brake On\r\n");
            pin_fwd.setval(1);
            pin_rvs.setval(1);
        } 
        else
        {
            Serial.puts("Command not understood. 'f'=Forward,'r'=Reverse,'0'=Off\r\n");
        }
        
    };

  protected:
    // Devices
    clixxIOGPIOPin pin_fwd;
    clixxIOGPIOPin pin_rvs;
 
};

// Main program Section. Simply setup an App class and let it run
int main(){
 
  App m;
  
  return m.run();

}

// Autogenerated interface between the event interface and application class
#include "serial-hbridge-callbacks.cpp"
