#ifndef TOOLCELL_H
#define TOOLCELL_H

#include <cstring>
#include "toolLib.h"

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
#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>

class ToolLib;

struct position
{
  int x;
  int y;
};

class CalendarCell : public QLabel
{
  Q_OBJECT
  Q_PROPERTY(int rowStr READ rowStr WRITE setRowStr)
  Q_PROPERTY(int colStr READ colStr WRITE setColStr)
  Q_PROPERTY(int focusedRowStr READ focusedRowStr WRITE setFocusedRowStr)
  Q_PROPERTY(int focusedColStr READ focusedColStr WRITE setFocusedColStr)
  Q_PROPERTY(int color_B READ color_B WRITE setColor_B)

public:
  static bool focused;
  bool mouseClicked;

  static int focused_x;
  static int focused_y;

  CalendarCell(QWidget *parent = 0);
  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:
  position getLayoutPos();
  int rowStr() const;
  void setRowStr(const int len);
  int colStr() const;
  void setColStr(const int wid);

  int focusedRowStr() const;
  void setFocusedRowStr(const int len);
  int focusedColStr() const;
  void setFocusedColStr(const int wid);
  int color_B() const;
  void setColor_B(const int blue);

  int m_len;
  int m_wid;
  int m_focusedLen;
  int m_focusedWid;
  int m_color_B;

  ToolLib *tool;
  position layoutPos;
  QString labelText;
  QGridLayout *calendarMainWidget;
};

#endif // TOOLCELL_H