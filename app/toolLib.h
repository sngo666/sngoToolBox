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
#include <QDateTime>
#include <QLocale>

using namespace std;


struct monthInfo
{
  int year;
  int length;
  int firstDay;
  int lastDay;
  int month;
};

namespace tool
{
  class ToolLib;
}

class ToolLib
{
public:
  ToolLib(void);
  ~ToolLib();
  int getWeekOrdinal(QString str);
  void Sleep(int msec);
  int getMonthDay(int month, int year);
  inline bool isLeapYear(int year);
  monthInfo getMonthInfo(int month, int year);
};

#endif