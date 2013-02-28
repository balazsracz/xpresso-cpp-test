#include <stdlib.h>
#include "can.h"

#include "third_party/nxp/rom_drivers.h"

ROM **rom = (ROM **)0x1fff1ff8;

#ifdef USE_ROM_CAN
extern "C" {
// Overrides the system's weak interrupt handler and calls the builtin ROM interrupt handler.
void CAN_IRQHandler (void){
  (*rom)->pCAND->isr();
}
}  // extern C

/* Callback function prototypes */
void CAN_rx(uint8_t msg_obj_num);
void CAN_tx(uint8_t msg_obj_num);
void CAN_error(uint32_t error_info);


CAN_CALLBACKS callbacks = {
   CAN_rx,
   CAN_tx,
   CAN_error,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
};


void CAN_rx(uint8_t msg_obj_num){
  CAN_MSG_OBJ msg_obj;
  /* Determine which CAN message has been received */
  msg_obj.msgobj = msg_obj_num;

  /* Now load up the msg_obj structure with the CAN message */
  (*rom)->pCAND->can_receive(&msg_obj);

  if (msg_obj_num == 1)
  {
    /* Simply transmit CAN frame (echo) with with ID +0x100 via buffer 2 */
    msg_obj.msgobj = 2;
    msg_obj.mode_id += 0x100;
    (*rom)->pCAND->can_transmit(&msg_obj);
    LPC_GPIO0->DATA ^= (1<<7);
  }

  return;
}

/*  CAN transmit callback */
/*  Function is executed by the Callback handler after
    a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num){
  return;
}

/*  CAN error callback */
/*  Function is executed by the Callback handler after
    an error has occured on the CAN bus */
void CAN_error(uint32_t error_info){
  return;
}

uint32_t ClkInitTable[2] = {
  0x00000000UL, // CANCLKDIV
  0x00001C57UL  // CAN_BTR
};

// Putting this inside of the #ifdef will ensure that we get a linker error if we do not have the interrupt routine setup.
void CANHandler::Initialize() {
  /* Initialize the CAN controller */
  (*rom)->pCAND->init_can(&ClkInitTable[0], 1);
  /* Configure the CAN callback functions */
  (*rom)->pCAND->config_calb(&callbacks);

  /* Enable the CAN Interrupt */
  NVIC_EnableIRQ(CAN_IRQn);

  CAN_MSG_OBJ msg_obj;

  /* Send a simple one time CAN message */
   msg_obj.msgobj  = 0;
   msg_obj.mode_id = 0x345;
   msg_obj.mask    = 0x0;
   msg_obj.dlc     = 4;
   msg_obj.data[0] = 'T';  //0x54
   msg_obj.data[1] = 'E';  //0x45
   msg_obj.data[2] = 'S';  //0x53
   msg_obj.data[3] = 'T';  //0x54
   (*rom)->pCAND->can_transmit(&msg_obj);

   /* Configure message object 1 to receive all 11-bit messages 0x400-0x4FF */
   msg_obj.msgobj = 1;
   msg_obj.mode_id = 0x400;
   msg_obj.mask = 0x700;
   (*rom)->pCAND->config_rxmsgobj(&msg_obj);
}



#endif
