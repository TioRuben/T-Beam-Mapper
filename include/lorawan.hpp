#include <Arduino.h>
#include <Arduino_LoRaWAN_ChirpStack.h>

class cLoraTVT : public Arduino_LoRaWAN_ChirpStack_eu868
{
public:
  cLoraTVT(){};

protected:
  // you'll need to provide implementations for each of the following.
  virtual bool GetOtaaProvisioningInfo(Arduino_LoRaWAN::OtaaProvisioningInfo *) override;
  virtual void NetSaveFCntUp(uint32_t uFCntUp) override;
  virtual void NetSaveFCntDown(uint32_t uFCntDown) override;
  virtual void NetSaveSessionInfo(const SessionInfo &Info, const uint8_t *pExtraInfo, size_t nExtraInfo) override;
};

void initLora(void);
void loraLoop(void);
void sendPosition(double latitude, double longitude);
void sendDone(void *pCtx, bool fSuccess);
void loraWanSleep(void);