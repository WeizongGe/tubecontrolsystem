#include "model/tubeControlSystemApp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
      return tubeControlSystemApp::instance()->run(argc, argv);
}
