/*
 * can.h
 *
 *  Created on: Feb 28, 2013
 *      Author: bracz
 */

#ifndef CAN_H_
#define CAN_H_
#include "config.h"


#ifdef USE_ROM_CAN

class CANHandler {
public:
  void Initialize();
};


#endif


#endif /* CAN_H_ */
