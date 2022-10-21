#ifndef TOOLLIB_H
#define TOOLLIB_H

#include <iostream>
#include <cstring>

#include <QtGlobal>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QThread>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>

using namespace std;

namespace tool
{
  class ToolLib;
}

class ToolLib
{
public:
  ToolLib(void);
  ~ToolLib();

public:
  void Sleep(int msec);
};

#endif