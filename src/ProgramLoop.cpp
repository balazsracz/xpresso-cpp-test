/*
 * ProgramLoop.cpp
 *
 *  Created on: Feb 26, 2013
 *      Author: bracz
 */
#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include "ProgramLoop.h"


extern "C" {
// Trampoline from C main file to C++ main class.
void RunProgramLoop() {
  //ProgramLoop lp;
  ProgramLoop* loop = new ProgramLoop();
  loop->Init();
  loop->Run();
  // should never get here.
  while(1) {
    // Enter an infinite loop, just incrementing a counter
    volatile static int i = 0 ;
    while(1) {
      const int bit = 19;
      const int mask = (1<<bit)-1;
      if (!(i & mask)) {
        if ((i >> bit) & 1) {
          LPC_GPIO0->DATA |= (1<<7);
        } else {
          LPC_GPIO0->DATA &= ~(1<<7);
        }
      }
      i++ ;
    }
  }
}
}

ProgramLoop::ProgramLoop() {
  // TODO Auto-generated constructor stub

}

ProgramLoop::~ProgramLoop() {
  // TODO Auto-generated destructor stub
}

void ProgramLoop::Init() {}
void ProgramLoop::Run() {}
