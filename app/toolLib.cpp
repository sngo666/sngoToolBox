#include "toolLib.h"

ToolLib::ToolLib(void)
{
}
void ToolLib::Sleep(int msec)
{
  QTime dieTime = QTime::currentTime().addMSecs(msec);
  while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

ToolLib::~ToolLib()
{
}
