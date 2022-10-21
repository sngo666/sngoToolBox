#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "./app/Calendar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setFixedSize(this->width(), this->height());

  this->setQssFile();
  this->calendarWidget = new Calendar();

  connect(ui->openCalendar, SIGNAL(clicked()), this, SLOT(openCalendar_clicked()));
}

void MainWindow::setQssFile()
{
  QFile file(QString("%1/qss/myqss.qss").arg(QDir::currentPath()));
  file.open(QFile::ReadOnly);
  qApp->setStyleSheet(file.readAll());
  file.close();
}

void MainWindow::openCalendar_clicked()
{
  calendarWidget->show();
}

MainWindow::~MainWindow()
{
  delete calendarWidget;
  delete ui;
}
