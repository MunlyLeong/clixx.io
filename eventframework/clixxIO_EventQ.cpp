#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "clixxIO.hpp"

#define INTERVAL 2

int howmany = 0;

class clixxIOTimer {
  public:
  private:
    int durationmSecs;
};

class clixxIOMsgQ {

  public:                    // begin public section
    clixxIOMsgQ(int initialAge);     // constructor
    ~clixxIOMsgQ();                  // destructor
    
//    int peekMsg() const;
//    int getMsg();
    
    int run();  // Main event for running
    
 private:                   // begin private section
    int itsAge;              // member variable

    int eventlist[10];
    
};

// constructor of Cat,
clixxIOMsgQ::clixxIOMsgQ(int initialAge)
{
  itsAge = initialAge;
}

clixxIOMsgQ::~clixxIOMsgQ()                 // destructor, just an example
{
}

// GetAge, Public accessor function
// returns value of itsAge member
int clixxIOMsgQ::run()
{
   return itsAge;
}

void timer_wakeup (int interval)
{
   struct itimerval tout_val;

   signal(SIGALRM,timer_wakeup);

   howmany += INTERVAL;
   
   printf("\n%d sec up partner, Wakeup!!!\n",howmany);
   tout_val.it_interval.tv_sec = 0;
   tout_val.it_interval.tv_usec = 0;
   tout_val.it_value.tv_sec = interval; /* 10 seconds timer */
   tout_val.it_value.tv_usec = 0;
   
   setitimer(ITIMER_REAL, &tout_val,0);
   
}

void timer_setup (int interval)
{
  struct itimerval tout_val;
  
  tout_val.it_interval.tv_sec = 0;
  tout_val.it_interval.tv_usec = 0;
  tout_val.it_value.tv_sec = INTERVAL;  // 10 seconds timer 
  tout_val.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &tout_val,0);
  signal(SIGALRM,timer_wakeup); // set the Alarm signal capture 
 
}

void exit_func (int i)
{
    signal(SIGINT,exit_func);
    printf("\nBye Bye!!!\n");
    exit(0);
}

clixxIOApp::clixxIOApp()
{
  
  // Setup a signal handler for exit
  signal(SIGINT,exit_func);
  
}

clixxIOApp::~clixxIOApp()
{
  
}

void *pMainClass;	

int clixxIOApp::run()
{
	
  C_startedevent(pMainClass);
  
  puts("Application now in main loop");
  
  for (;;);
  
}

// Set the object address of the App class in main() 
// Pointer to the address of the Users Application Object
void setMainAppPtr(void *mainClass)
{
  pMainClass = mainClass;	

  printf("MainClass set to %p\n",mainClass);
}

int addLoopEvent(void (*function)(int))
{

}

int addTimerEvent(int secs, void (*function)())
{
  
  timer_setup(secs);
  
}

int addInterruptEvent(int secs, void (*function)())
{
  
}

int addSerialInterruptEvent(int secs, void (*function)())
{
  
}

//--Dummy main function
int main0 ()
{
  
  signal(SIGINT,exit_func);
  
  timer_setup(2);
  
  while (1)
  {
    //printf("!");
  }
  
  return 0;

}
