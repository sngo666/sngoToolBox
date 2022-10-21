#ifndef CALENDAR_H
#define CALENDAR_H

#include "toolCell.h"

#include <QtCore>
#include <QtGlobal>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <cmath>
#include <QProcess>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QPushButton>
#include <QImage>
#include <QFileDialog>
#include <QDialog>
#include <map>
#include <vector>
#include <array>
#include <QGraphicsEffect>
using namespace std;

namespace Ui
{
  class Calendar;
}

class Calendar : public QWidget
{
  Q_OBJECT

public slots:
  bool eventFilter(QObject *watched, QEvent *evt) override;

public:
  explicit Calendar(QWidget *parent = nullptr);
  ~Calendar();

private:
  vector<vector<CalendarCell *>> calendarUnits;

  void setShadow();
  void Init();

  void setQssFile();
  vector<vector<CalendarCell *>> getCalendarUnits();

  ToolLib *tool;
  Ui::Calendar *ui;
};

#endif // CALENDAR_H
