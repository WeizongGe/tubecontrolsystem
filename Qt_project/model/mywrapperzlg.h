#ifndef MYWRAPPERZLG_H
#define MYWRAPPERZLG_H
#include <QObject>
#include <memory>
#include <unordered_map>
#include "zlgcan.h"
using std::vector;

class ZlgCan
{
public:
    enum class ChIdx{
        ZERO = 0,
        ONE = 1
    };
public:

    DEVICE_HANDLE hDevice = nullptr;
    IProperty* pIpr;
    vector<char*> hChannels = {nullptr, nullptr}; //void* can't as vector element
    bool DEVICE_START = false;
    unsigned CHANNEL_START = 0;

private:
    static ZCAN_CHANNEL_INIT_CONFIG CFG;
    static const std::string BaudSufix;
/// Member Functions:
public:
/// CONSTRUCTOR:
    ZlgCan(unsigned num = 2);
    int DeviceInit();
    int ChannelInit(ChIdx idx);
    void ProcessERROR(int eCODE);


    bool Read(CHANNEL_HANDLE hCh);
    bool Write(CHANNEL_HANDLE hCh);

    uint32_t ReadDataProcess(BYTE* data, unsigned size);
    bool GetChannelStart(ChIdx idx){ return (CHANNEL_START & 1 << static_cast<int>(idx)) != 0x00;}
    void SetChannelStart(ChIdx idx){ CHANNEL_START |= 1<<static_cast<int>(idx); }
    bool CHANNEL0_START(){ return GetChannelStart(ChIdx::ZERO);}
    bool CHANNEL1_START(){ return GetChannelStart(ChIdx::ONE);}

private:   
    void CFG_INIT();
    bool myDeviceInit(unsigned dType= (ZCAN_USBCAN2),            // 调用顺序
                     unsigned dIdx = 0,                         //   1↓
                     unsigned reverse = 0);                     //   2↓
    bool myIPropertyInit();                                       //   3↓
    bool mySetBaurdRate(ChIdx idx, std::string rate = "500000");  //   4↓
    CHANNEL_HANDLE myChannelInit(ChIdx idx);
};


#endif // MYWRAPPERZLG_H
