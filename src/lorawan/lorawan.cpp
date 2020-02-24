#include <Arduino.h>
#include <arduino_lmic.h>
#include <hal/hal.h>
#include <Arduino_LoRaWAN_ChirpStack.h>
#include "lorawan.hpp"
#include "oled.hpp"
#include "main-tasks.hpp"

cLoraTVT loraTVT{};

const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = LMIC_UNUSED_PIN, // was "14,"
    .dio = {26, 33, 32},
};

uint8_t buffer[8];

void initLora(void)
{
  if (!loraTVT.begin(lmic_pins))
  {
    Serial.println("Error initializing LoRa RF");
  }
  loraTVT.SetLinkCheckMode(true);
}

void loraLoop(void)
{
  loraTVT.loop();
}

bool cLoraTVT::GetOtaaProvisioningInfo(OtaaProvisioningInfo *pInfo)
{
  OtaaProvisioningInfo otaaInfo = {
      {CFG_APPKEY},
      {CFG_DEVEUI},
      {CFG_APPEUI}};
  *pInfo = otaaInfo;
  return true;
}

void cLoraTVT::NetSaveFCntDown(uint32_t uFCntDown)
{
  // save uFcntDown somwwhere
}

void cLoraTVT::NetSaveFCntUp(uint32_t uFCntUp)
{
  // save uFCntUp somewhere
}

void cLoraTVT::NetSaveSessionInfo(
    const SessionInfo &Info,
    const uint8_t *pExtraInfo,
    size_t nExtraInfo)
{
  // save Info somewhere.
}

void sendPosition(double latitude, double longitude)
{
  int32_t uLatitude = (int32_t)(latitude * 100000);
  int32_t uLongitude = (int32_t)(longitude * 100000);
  buffer[0] = uLatitude >> 24;
  buffer[1] = uLatitude >> 16;
  buffer[2] = uLatitude >> 8;
  buffer[3] = uLatitude;
  buffer[4] = uLongitude >> 24;
  buffer[5] = uLongitude >> 16;
  buffer[6] = uLongitude >> 8;
  buffer[7] = uLongitude;
  loraTVT.SendBuffer(buffer, sizeof(buffer), &sendDone);
}

void sendDone(void *pCtx, bool fSuccess)
{
  if (fSuccess)
  {
    Serial.println("Send Success");
    displayLora("Send Success");
  }
  else
  {
    Serial.println("Send Fail");
    displayLora("Send Fail");
  }
}

void loraWanSleep(void)
{
  loraTVT.Shutdown();
}