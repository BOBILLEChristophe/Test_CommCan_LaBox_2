/*

  CanMsg.cpp

  v 0.4 - 08/12/23
  v 0.5 - 09/12/23 : Ajout du retour d'information au programme de test. C'est la mesure de courant qui a ete choisie
                    pour cela lignes 83 a 97 du programme.
  v 0.5.1 - 09/12/23 : Fix oubli break  case 0xFE:
                                          TrackManager::setMainPower(frameIn.data[0] ? POWERMODE::ON : POWERMODE::OFF);
                                        break;
  v 0.5.2 - 09/12/23
  v 0.5.3 - 10/12/23
  v 0.5.4 - 10/12/23 : Add POWERMODE::OVERLOAD

  /*******************************************************************************************************                     
  v 0.6.0 - 11/12/23 : Adoption d'un nouveau format de messages totalement incompatible avec les anciens 
*/

#include "CanMsg.h"

gpio_num_t CanMsg::RxPin = GPIO_NUM_4;               // Optional, default Rx pin is GPIO_NUM_4
gpio_num_t CanMsg::TxPin = GPIO_NUM_5;               // Optional, default Tx pin is GPIO_NUM_5

// gpio_num_t CanMsg::RxPin = GPIO_NUM_22;               // Optional, default Rx pin is GPIO_NUM_4
// gpio_num_t CanMsg::TxPin = GPIO_NUM_23;               // Optional, default Tx pin is GPIO_NUM_5

uint32_t CanMsg::DESIRED_BIT_RATE = 1000UL * 1000UL;  // 1 Mb/s;

void CanMsg::setup() {
  Serial.printf("[CanConfig %d] : Configure ESP32 CAN\n", __LINE__);
  ACAN_ESP32_Settings settings(DESIRED_BIT_RATE);
  settings.mRxPin = RxPin;
  settings.mTxPin = TxPin;

  uint32_t errorCode;

  // with filter
  // const ACAN_ESP32_Filter filter = ACAN_ESP32_Filter::singleExtendedFilter(
  //     ACAN_ESP32_Filter::data, 0xF << 7, 0x1FFFF87F);
  // errorCode = ACAN_ESP32::can.begin(settings, filter);

  // without filter
  errorCode = ACAN_ESP32::can.begin(settings);
  Serial.printf("[CanConfig %d] : config without filter\n", __LINE__);

  if (errorCode == 0)
    Serial.printf("[CanConfig %d] : configuration OK !\n", __LINE__);
  else {
    Serial.printf("[CanConfig %d] : configuration error 0x%x\n", __LINE__, errorCode);
    return;
  }
}



/*--------------------------------------
  Envoi CAN
  --------------------------------------*/

void CanMsg::sendMsg(CANMessage &frame) {
  if (0 == ACAN_ESP32::can.tryToSend(frame))
    Serial.printf("Echec envoi message CAN\n");
  else
    Serial.printf("Envoi commande 0x%0X\n", (frame.id & 0x1FE0000) >> 17);
}

auto parseMsg = [](CANMessage &frame, byte prio, byte cmde, byte resp) -> CANMessage {
  // Pour tests seulement
  uint16_t hash = 0x1801;

  frame.id |= prio << 25;  // Priorite
  frame.id |= cmde << 17;  // Commande
  frame.id |= resp << 16;  // Reponse : Commande = 0 / Reponse = 1
  frame.id |= hash;        // Hash
  frame.ext = true;
  return frame;
};

void CanMsg::sendMsg(byte prio, byte cmde, byte resp) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 0;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 1;
  frame.data[0] = data0;  // Fonction
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 2;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1, byte data2) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 3;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  frame.data[2] = data2;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1, byte data2, byte data3) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 4;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  frame.data[2] = data2;
  frame.data[3] = data3;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1, byte data2, byte data3, byte data4) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 5;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  frame.data[2] = data2;
  frame.data[3] = data3;
  frame.data[4] = data4;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1, byte data2, byte data3, byte data4, byte data5) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 6;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  frame.data[2] = data2;
  frame.data[3] = data3;
  frame.data[4] = data4;
  frame.data[5] = data5;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1, byte data2, byte data3, byte data4, byte data5, byte data6) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 7;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  frame.data[2] = data2;
  frame.data[3] = data3;
  frame.data[4] = data4;
  frame.data[5] = data5;
  frame.data[6] = data6;
  CanMsg::sendMsg(frame);
}

void CanMsg::sendMsg(byte prio, byte cmde, byte resp, byte data0, byte data1, byte data2, byte data3, byte data4, byte data5, byte data6, byte data7) {
  CANMessage frame;
  frame = parseMsg(frame, prio, cmde, resp);
  frame.len = 8;
  frame.data[0] = data0;  // Fonction
  frame.data[1] = data1;
  frame.data[2] = data2;
  frame.data[3] = data3;
  frame.data[4] = data4;
  frame.data[5] = data5;
  frame.data[6] = data6;
  frame.data[7] = data7;
  CanMsg::sendMsg(frame);
}