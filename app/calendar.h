#ifndef CALENDAR_H
#define CALENDAR_H

#include "toolCell.h"
#include "toolLib.h"

#include <map>
#include <vector>
#include <array>
#include <cmath>

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
#include <QProcess>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QPushButton>
#include <QImage>
#include <QFileDialog>
#include <QDialog>
#include <QGraphicsEffect>
#include <QDateTime>
#include <QLocale>
#include <QListWidgetItem>
#include <QListWidget>
#include <QSize>
#include <QScroller>
#include <QAbstractItemView>

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
  ToolLib *tool;
  Ui::Calendar *ui;
  vector<vector<CalendarCell *>> calendarUnits;
  int selectedMonth;
  int selectedYear;
  int selectedDay;
  NoteInfo testNoteInfo = {2022, 10, 25, 17, 58, "just a test just a test just a test just a test ", "remember this is just a test.", true};

  void setShadow();
  void Init();
  void setQssFile();
  void refreshCalendarForm();
  void createNote(NoteInfo m_info);

  vector<vector<CalendarCell *>> getCalendarUnits();
};

#endif // CALENDAR_H
