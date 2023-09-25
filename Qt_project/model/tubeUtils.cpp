/*********************************************************
* Author: Haowen Chen
* Date: 2020/10/31
* Mail: chenhaowen01@qq.com
*
* 全局通用的工具类函数
*********************************************************/

#include <QDateTime>
#include "tubeUtils.h"

// return current time stamp (seconds)
double getCurrentTime()
{
    return QDateTime::currentMSecsSinceEpoch() / 1000.0;
}

/*********************************************************
                       Timer



**********************************************************/
using namespace MyTime;
Timer::Timer()
{
    base = 0;
    running = false;
}

void Timer::start()
{
    if(!running)
    {
        base = getCurrentTime() + base;
        running = true;
    }
}

void Timer::pause()
{
    if(running)
    {
        base =getCurrentTime() - base;
        running = false;
    }
}

void Timer::stop()
{
    if(running)
    {
        base = 0;
        running =false;
    }
}

void Timer::restart()
{
    if(running)
    {
        stop();
        start();
    }
}
double Timer::nowTime()
{
    return getCurrentTime() - base;
}
