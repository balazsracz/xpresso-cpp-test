/*
 * can.h
 *
 *  Created on: Feb 28, 2013
 *      Author: bracz
 */

#ifndef CAN_H_
#define CAN_H_
#include "config.h"
// TODO: replace this with a stdint include
#include "third_party/nxp/rom_drivers.h"


#ifdef USE_ROM_CAN

class CANHandler {
public:
  void Initialize();
  void SendFrame(uint32_t id, int dlc, int32_t d1, int32_t d2);
};


#endif


#endif /* CAN_H_ */
