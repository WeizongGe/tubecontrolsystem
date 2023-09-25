#include "mywrapperzlg.h"

ZCAN_CHANNEL_INIT_CONFIG GetCFGInit();
ZCAN_CHANNEL_INIT_CONFIG ZlgCan::CFG = GetCFGInit();
const std::string ZlgCan::BaudSufix = "/baud_rate";
namespace ERROR_DEFINITION {
    constexpr const int CHANNEL_ALREADY_START = -2;
    constexpr const int DEVICE_ALREADY_START = -1;
    constexpr const int NO_ANY_ERROR = 0;
    constexpr const int DEVICE_ERROR = 1;
    constexpr const int IPROPERTY_ERROR = 2;
    constexpr const int BAURD_RATE_SET_ERROR = 3;
    constexpr const int CHANNEL_ERROR = 4;
    constexpr const int OCCUPYID_ERROR = 5;
};
using namespace ERROR_DEFINITION;

ZlgCan::ZlgCan(unsigned num)
{
    hChannels.assign(num, nullptr);
}

int ZlgCan::DeviceInit()
{
    if(DEVICE_START)
    {
       return DEVICE_ALREADY_START;
    }
    if(!myDeviceInit())
        return DEVICE_ERROR;
    if(!myIPropertyInit())
        return IPROPERTY_ERROR;
    DEVICE_START = true;
    return NO_ANY_ERROR;
}

int ZlgCan::ChannelInit(ChIdx idx)
{
    if(GetChannelStart(idx))
    {
        return CHANNEL_ALREADY_START;
    }
    if(!mySetBaurdRate(idx))
        return BAURD_RATE_SET_ERROR;
    if(myChannelInit(idx) == INVALID_CHANNEL_HANDLE)
        return CHANNEL_ERROR;
    if(ZCAN_StartCAN(hChannels[static_cast<int>(idx)]) != STATUS_OK)
        return OCCUPYID_ERROR;
    SetChannelStart(idx);
    return NO_ANY_ERROR;
}

void ZlgCan::ProcessERROR(int eCODE)
{
    switch(eCODE)
    {
        case 1:break;
        case 2:ZCAN_CloseDevice(hDevice);break;
        case 3:ZCAN_CloseDevice(hDevice);
               ReleaseIProperty(pIpr);break;
        case 4:
        case 5:ZCAN_ClearBuffer(hChannels[0]);
               ZCAN_ResetCAN(hChannels[0]);break;
        default: ;
    }
}

bool ZlgCan::myDeviceInit(unsigned int dType, unsigned int dIdx, unsigned int reverse)
{
    hDevice = ZCAN_OpenDevice(dType, dIdx, reverse);
    return INVALID_DEVICE_HANDLE != hDevice;
}

bool ZlgCan::myIPropertyInit()
{
    pIpr = GetIProperty(hDevice);
    return pIpr != nullptr;
}

bool ZlgCan::mySetBaurdRate(ChIdx idx , std::string rate)
{
    return pIpr->SetValue((std::to_string(static_cast<int>(idx)) + BaudSufix).c_str(),
                           rate.c_str()) == STATUS_OK;
}

CHANNEL_HANDLE ZlgCan::myChannelInit(ChIdx idx)
{
    hChannels[static_cast<int>(idx)] =
                (char*)ZCAN_InitCAN(hDevice,
                             static_cast<int>(idx),
                             &CFG);
    return hChannels[static_cast<int>(idx)];
}

ZCAN_CHANNEL_INIT_CONFIG GetCFGInit()
{
    ZCAN_CHANNEL_INIT_CONFIG cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.can_type = TYPE_CAN;
    cfg.can.filter = 0;
    cfg.can.mode = 0;                   //正常模式, 1为只听模式
    cfg.can.acc_code = 0;
    cfg.can.acc_mask = 0xffffffff;
    return cfg;
}
