#include "Calendar.h"
#include "ui_Calendar.h"

#include "toolCell.h"

Calendar::Calendar(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::Calendar)
{

  ui->setupUi(this);
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
  this->setFixedSize(this->width(), this->height());
  this->setAttribute(Qt::WA_QuitOnClose, false);
  ui->calendarWidget->installEventFilter(this);
  tool = new ToolLib();

  // this->setQssFile();

  this->Init();
}

void Calendar::setQssFile()
{
  QFile file(QString("%1/qss/myqss.qss").arg(QDir::currentPath()));
  file.open(QFile::ReadOnly);
  qApp->setStyleSheet(file.readAll());
  file.close();
}

void Calendar::Init()
{
  this->calendarUnits = this->getCalendarUnits();
  ui->calendarWidget->setStyleSheet("QWidget#calendarWidget{border-radius:20px;background-color:rgb(231, 255, 255);}");
  QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
  shadow->setOffset(0, 0);
  shadow->setColor(Qt::black);
  shadow->setBlurRadius(10);
  ui->calendarFormWidget->setGraphicsEffect(shadow);

  ui->calendarFormWidget->setStyleSheet("QWidget#calendarFormWidget{background-color:rgb(221, 224, 255);}");
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      this->calendarUnits[i][j]->setStyleSheet("background-color: rgb(231, 255, 255);");
    }
  }

  this->setShadow();
}

void Calendar::setShadow()
{
  ui->calendarWidget->setStyleSheet("#calendarWidget{background: #FFFFFF;}");
  QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
  shadow->setOffset(0, 0);
  shadow->setColor(Qt::black);
  shadow->setBlurRadius(15);
  ui->calendarWidget->setGraphicsEffect(shadow);
  this->setAttribute(Qt::WA_TranslucentBackground);
  // ui->calendarWidget->setMargin(24);
}
bool Calendar::eventFilter(QObject *watched, QEvent *evt)
{
  static QPoint mousePoint;
  static bool mousePressed = false;

  QMouseEvent *event = static_cast<QMouseEvent *>(evt);
  if (event->type() == QEvent::MouseButtonPress)
  {
    if (event->button() == Qt::LeftButton)
    {
      mousePressed = true;
      mousePoint = event->globalPos() - this->pos();
      return true;
    }
    else
    {
      // exit(0); // 右击事件直接退出程序
    }
  }
  else if (event->type() == QEvent::MouseButtonRelease)
  {
    mousePressed = false;
    return true;
  }
  else if (event->type() == QEvent::MouseMove)
  {
    if (mousePressed && (event->buttons() & Qt::LeftButton))
    {
      this->move(event->globalPos() - mousePoint);
      return true;
    }
  }
  return QWidget::eventFilter(watched, event);
}

vector<vector<CalendarCell *>> Calendar::getCalendarUnits()
{
  vector<vector<CalendarCell *>> m_vv;
  for (int i = 0; i < 8; i++)
  {
    vector<CalendarCell *> m_v;
    m_vv.push_back(m_v);
  }

  array<CalendarCell *, 7> a0{ui->L0_0, ui->L0_1, ui->L0_2, ui->L0_3, ui->L0_4, ui->L0_5, ui->L0_6};
  m_vv[0].insert(m_vv[0].end(), a0.begin(), a0.end());

  array<CalendarCell *, 7> a1{ui->L1_0, ui->L1_1, ui->L1_2, ui->L1_3, ui->L1_4, ui->L1_5, ui->L1_6};
  m_vv[1].insert(m_vv[1].end(), a1.begin(), a1.end());

  array<CalendarCell *, 7> a2{ui->L2_0, ui->L2_1, ui->L2_2, ui->L2_3, ui->L2_4, ui->L2_5, ui->L2_6};
  m_vv[2].insert(m_vv[2].end(), a2.begin(), a2.end());

  array<CalendarCell *, 7> a3{ui->L3_0, ui->L3_1, ui->L3_2, ui->L3_3, ui->L3_4, ui->L3_5, ui->L3_6};
  m_vv[3].insert(m_vv[3].end(), a3.begin(), a3.end());

  array<CalendarCell *, 7> a4{ui->L4_0, ui->L4_1, ui->L4_2, ui->L4_3, ui->L4_4, ui->L4_5, ui->L4_6};
  m_vv[4].insert(m_vv[4].end(), a4.begin(), a4.end());

  array<CalendarCell *, 7> a5{ui->L5_0, ui->L5_1, ui->L5_2, ui->L5_3, ui->L5_4, ui->L5_5, ui->L5_6};
  m_vv[5].insert(m_vv[5].end(), a5.begin(), a5.end());

  array<CalendarCell *, 7> a6{ui->L6_0, ui->L6_1, ui->L6_2, ui->L6_3, ui->L6_4, ui->L6_5, ui->L6_6};
  m_vv[6].insert(m_vv[6].end(), a6.begin(), a6.end());

  array<CalendarCell *, 7> a7{ui->L7_0, ui->L7_1, ui->L7_2, ui->L7_3, ui->L7_4, ui->L7_5, ui->L7_6};
  m_vv[7].insert(m_vv[7].end(), a7.begin(), a7.end());
  return m_vv;
}

Calendar::~Calendar()
{
  delete ui;
}
