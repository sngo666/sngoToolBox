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

int ToolLib::getWeekOrdinal(QString str)
{
  string week = str.toStdString();
  map<string, int> weekList = {
      {"Mon", 1},
      {"Tus", 2},
      {"Wed", 3},
      {"Thu", 4},
      {"Fri", 5},
      {"Sat", 6},
      {"Sun", 7}};
  return weekList[week];
}

monthInfo ToolLib::getMonthInfo(int month, int year)
{
  monthInfo info;
  info.year = year;
  info.month = month;
  info.length = this->getMonthDay(month, year);

  int M = (month < 3) ? (month + 12) : (month);
  int temp = (int)(year / 400) - 2 * (int)(year / 100) + (year % 100) + (int)((year % 100) / 4) + (int)(13 * (M + 1) / 5);
  info.firstDay = temp % 7;
  info.lastDay = (temp + info.length - 1) % 7;

  return info;
}

inline bool ToolLib::isLeapYear(int year)
{
  return (year % 4 == 1);
}
int ToolLib::getMonthDay(int month, int year)
{
  if (month > 12)
    return -1;
  map<int, int> monthList = {
      {1, 31},
      {2, 28},
      {3, 31},
      {4, 30},
      {5, 31},
      {6, 30},
      {7, 31},
      {8, 31},
      {9, 30},
      {10, 31},
      {11, 30},
      {12, 31}};
  if (month == 2)
    return (this->isLeapYear(year) ? (monthList[month] + 1) : monthList[month]);
  else
    return monthList[month];
}

ToolLib::~ToolLib()
{
}

