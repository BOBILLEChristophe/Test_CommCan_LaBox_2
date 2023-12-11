

#include "CanMsg.h"
#include "LaBoxCmd.h"

LaBoxCmd::LaBoxCmd(uint8_t id, uint8_t hash)
  : mHash(hash),
    mDebug(false),
    mPower(false) {}

LaBoxCmd::~LaBoxCmd() {
  if (mDebug)
    Serial.println(F("### Destroying controller"));
}

void LaBoxCmd::setup() {
}

bool ping() {
  const byte cmde = 0x18;
  const byte resp = 0x00;
  CanMsg::sendMsg(0, cmde, resp);
}

bool LaBoxCmd::setPower(bool power) {
  const byte cmde = 0xFE;
  const byte resp = 0x00;
  CanMsg::sendMsg(0, cmde, resp, power);
  mPower = power;
  return power;
}

bool LaBoxCmd::setThrottle(Loco *loco) {
  const byte cmde = 0xF0;
  const byte resp = 0x00;
  CanMsg::sendMsg(0, cmde, resp, loco->address & 0xFF00, loco->address & 0x00FF, loco->speed, loco->direction);
  return true;
}

bool LaBoxCmd::toggleThrottleDir(Loco *loco) {
  const byte cmde = 0xF0;
  const byte resp = 0x00;
  loco->direction = !loco->direction;
  CanMsg::sendMsg(0, cmde, resp, loco->address & 0xFF00, loco->address & 0x00FF, loco->speed, loco->direction);
  return true;
}

bool LaBoxCmd::setFunction(Loco *loco, byte idx) {
  const byte cmde = 0xF1;
  const byte resp = 0x00;
  CanMsg::sendMsg(0, cmde, resp, loco->address & 0xFF00, loco->address & 0x00FF, idx, loco->fn[idx]);
  return true;
}

bool LaBoxCmd::toggleFunction(Loco *loco, byte idx) {
  const byte cmde = 0xF1;
  const byte resp = 0x00;
  loco->fn[idx] = !loco->fn[idx];
  CanMsg::sendMsg(0, cmde, resp, loco->address & 0xFF00, loco->address & 0x00FF, idx, loco->fn[idx]);
  return true;
}

bool LaBoxCmd::emergency() {
  const byte cmde = 0xFF;
  const byte resp = 0x00;
  CanMsg::sendMsg(0, cmde, resp);
  return true;
}

bool LaBoxCmd::writeCVByteMain(Loco *loco, byte CV, byte value) {
  const byte cmde = 0xF7;
  const byte resp = 0x00;
  CanMsg::sendMsg(0, cmde, resp, loco->address & 0xFF00, loco->address & 0x00FF, CV, value);
  return true;
}
