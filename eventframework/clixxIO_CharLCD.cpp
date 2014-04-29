#include "clixxIO.hpp"

// Delay times
const double ClixxIO_i2cLCD::DELAY = 0.0005;
const double ClixxIO_i2cLCD::PULSE = 0.0005;

// MCP23008 Register Numbers
const int ClixxIO_i2cLCD::IODIR = 0x00;
const int ClixxIO_i2cLCD::IPOL  = 0x01;
const int ClixxIO_i2cLCD::GPPU  = 0x06;
const int ClixxIO_i2cLCD::GPIO  = 0x09;

// Command bits
const int ClixxIO_i2cLCD::LCD_ENABLE  = 0x10; // Enable line
const int ClixxIO_i2cLCD::LCD_COMMAND = 0x20; // Command/Data select
const int ClixxIO_i2cLCD::LCD_DATA    = 0x0F; // Data bits

// Addresses
const int ClixxIO_i2cLCD::LCD_LINE_1 = 0x80;  // LCD RAM address for the 1st line
const int ClixxIO_i2cLCD::LCD_LINE_2 = 0xC0;  // LCD RAM address for the 2nd line

  /*" This class wraps control of the display and provides a simple set of
      methods to manage output.
  "*/
ClixxIO_i2cLCD::ClixxIO_i2cLCD(int deviceAddress, int bus){
    //" Constructor
    //"

    /*
    Initialise
    */
    where[0] = 0, where[1] = 0;
    
    // Fill buffer with spaces
	for (int l=0;l<2;l++)
	    for (int r=0;r<16;r++)
	        lines[l][r] = ' ';
	        
    i2cbus = new ClixxIO_I2cBus(bus);
    
    device = deviceAddress;
    
}
  /*--------------------------------------------------------------------------
  * Internal helpers
  *--------------------------------------------------------------------------*/

 void ClixxIO_i2cLCD::_writeLCD(unsigned char value, bool cmd){
    /*
     * Write command or data to the LCD
    */ 
    // Make Sure "EN" is 0 or low
    i2cbus->write(device, GPIO, 0x00);
    // Set "R/S" to 0 for a command, or 1 for data/characters
    unsigned char out = 0x00;
    
    if (!cmd)
      out = out | LCD_COMMAND;
      
    i2cbus->write(device, GPIO, out);
    // Put the HIGH BYTE of the data/command on D7-4
    out = out | ((value >> 4) & LCD_DATA);
    i2cbus->write(device, GPIO, out);
    // Set "EN" (EN= 1 or High)
    out = out | LCD_ENABLE;
    i2cbus->write(device, GPIO, out);
    // Wait At Least 450 ns!!!
    sleep(PULSE);
    // Clear "EN" (EN= 0 or Low)
    out = out & ~LCD_ENABLE;
    i2cbus->write(device, GPIO, out);
    // Wait 5ms for command writes, and 200us for data writes.
    sleep(DELAY);
    // Put the LOW BYTE of the data/command on D7-4
    out = (out & ~LCD_DATA) | (value & LCD_DATA);
    i2cbus->write(device, GPIO, out);
    // Set "EN" (EN= 1 or High)
    out = out | LCD_ENABLE;
    i2cbus->write(device, GPIO, out);
    // Wait At Least 450 ns!!!
    sleep(PULSE);
    // Clear "EN" (EN= 0 or Low)
    out = out & ~LCD_ENABLE;
    i2cbus->write(device, GPIO, out);
    // Wait 5ms for command writes, and 200us for data writes.
    sleep(DELAY);
}

void ClixxIO_i2cLCD::_update(){
    /* 
     * Update the display with the contents of the buffer
    */
    _writeLCD(LCD_LINE_1, true);
    for (int ch=0; ch<16;ch++)
      _writeLCD(ch, false);
    _writeLCD(LCD_LINE_2, true);
    for (int ch=0; 16;ch++)
      _writeLCD(ch, false);
    }

  // --------------------------------------------------------------------------
  // Public API
  // --------------------------------------------------------------------------

void ClixxIO_i2cLCD::setup()
{
    /*  
     * Set up the connection to the device
     */
    // Set up the IO expander
    i2cbus->write(device, GPIO,  0x00); // Clear outputs
    i2cbus->write(device, IODIR, 0x00); // Direction
    i2cbus->write(device, GPPU,  0x00); // Pull ups
    i2cbus->write(device, IPOL,  0x00); // Polarity
    // Initialise the display in 4 bit mode
    _writeLCD(0x33, true);
    _writeLCD(0x32, true);
    _writeLCD(0x28, true);
    // Set up initial state
    _writeLCD(0x0C, true);
    _writeLCD(0x06, true);
    _writeLCD(0x01, true);
}

void ClixxIO_i2cLCD::gotoXY(int x, int y){
    /*
     * Move the cursor to the given position
    */
    where[0] = x % 16;
    where[1] = y % 2 ;
}

void ClixxIO_i2cLCD::write(const char *text){
    /*
     * Write text to the current position
    */
    for (const char *ch = text;*ch != 0; ch++){
    
		lines[where[1]][where[0]] = *ch;
		gotoXY(where[0] + 1, where[1]);
		// Refresh
		_update();
	}
}

void ClixxIO_i2cLCD::writeline(int lineno, const char *text){
    /* 
     * Write a line of text justified
    */
    gotoXY(0,lineno);

	// Left Justify
	const char *ch = text;
	while (*ch == ' ')
		ch++;

    for (;*ch != 0; ch++){

		lines[where[1]][where[0]] = *ch;
		gotoXY(where[0] + 1, where[1]);
		// Refresh
		_update();
	}
}

void ClixxIO_i2cLCD::clear(){
    /* 
     * Clear the display
    */
    // Fill buffer with spaces
	for (int l=0;l<2;l++)
	    for (int r=0;r<16;r++)
	        lines[l][r] = ' ';

    _update();
}

/*----------------------------------------------------------------------------
 * Main program
 *----------------------------------------------------------------------------*/
#include "stdio.h"
#include "stdlib.h"

/*
int main(){

  // Set up WiringPi and connect to the IO expander
  ClixxIO_I2cBus *bus = new ClixxIO_I2cBus(1);
  if (bus == 0){
    puts("ERROR: Could not connect to device!");
    exit(1);
  }
  // Now create the LCD interface
  ClixxIO_i2cLCD *lcd = new ClixxIO_i2cLCD(0x20,1);
  lcd->setup();
  lcd->gotoXY(0, 0);
  lcd->write("clixx.io I2C-LCD");
  lcd->gotoXY(7, 1);
  lcd->write("It works!");
  sleep(3);
  lcd->gotoXY(0, 1);
  for (int i=0;i<16;i++)
	lcd->write(" ");
  char padding = 16;
  while (1){
    lcd->gotoXY(0, 1);
    for (int i=0;i<padding;i++)
		lcd->write(" ");
    lcd->write("It works!");
    sleep(0.1);
  }
}
*/