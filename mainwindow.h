
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./app/Calendar.h"
#include <QMainWindow>
#include <QDebug.h>
#include <QDesktopWidget>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QThread>
#include <QTimer>
#include <Qlabel>
#include <QtCore/qmath.h>
#include <cmath>
#include <ctime>

#include <cstring>
#include <qprocess.h>
#include <stdlib.h>
#include <vector>
#include <QMessageBox>

class Calendar;


QT_BEGIN_NAMESPACE namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public slots:
  void openCalendar_clicked();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:


  void setQssFile();
  Ui::MainWindow *ui;

  Calendar *calendarWidget;
};
#endif // MAINWINDOW_H
