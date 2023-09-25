#ifndef TUBEUTILS_H
#define TUBEUTILS_H

double getCurrentTime();
namespace MyTime {
    struct Timer{

      double base;
      bool running;

      Timer();

      void start();
      void pause();
      void stop();
      void restart();
      double nowTime();
      const Timer & operator=(const Timer & timer){
          if(this == &timer) return *this;
          base = timer.base;
          running = timer.running;
          return *this;
      }
    };
}


#endif // TUBEUTILS_H
