#include "toolCell.h"

bool CalendarCell::focused = false;
int CalendarCell::focused_x = -1;
int CalendarCell::focused_y = -1;

CalendarCell::CalendarCell(QWidget *parent) : QLabel(parent)
{
  setAlignment(Qt::AlignCenter);

  this->calendarMainWidget = parent->parent()->findChild<QGridLayout *>("calendarForm");
  this->tool = new ToolLib();
  mouseClicked = false;
}

void CalendarCell::enterEvent(QEvent *event)
{
  setCursor(Qt::PointingHandCursor);
  if (focused)
  {
    return;
  }
  this->layoutPos = this->getLayoutPos();

  setStyleSheet("border:2px solid;"
                "border-color: rgb(170, 170, 255);"
                "background-color: rgb(215, 255, 226)");
  QString name = this->objectName();

  int flag = 0;
  QTimer *timer = new QTimer(this);
  timer->start(30);
  connect(timer, &QTimer::timeout, [=]() mutable
          {
            if (flag < 10 && !this->underMouse() || this->mouseClicked)
            {
              timer->stop();
            }
            else
            {
              flag++;
            }
            if (this->underMouse() && flag >= 10)
            {
              setStyleSheet("border:2px solid;"
                            "border-color:  rgb(170, 170, 255) ;"
                            "background-color: rgb(231, 255, 226)");
              QPropertyAnimation *rowAnimation = new QPropertyAnimation();
              rowAnimation->setTargetObject(this);
              rowAnimation->setPropertyName("rowStr");
              rowAnimation->setDuration(100);

              rowAnimation->setKeyValueAt(0, this->calendarMainWidget->rowStretch(this->layoutPos.y));
              rowAnimation->setKeyValueAt(1, 18);

              QPropertyAnimation *colAnimation = new QPropertyAnimation();
              colAnimation->setTargetObject(this);
              colAnimation->setPropertyName("colStr");
              colAnimation->setDuration(100);

              colAnimation->setKeyValueAt(0, this->calendarMainWidget->columnStretch(this->layoutPos.x));
              colAnimation->setKeyValueAt(1, 18);

              rowAnimation->start();
              colAnimation->start();
              flag = 0;
              timer->stop();
            } });
}

void CalendarCell::leaveEvent(QEvent *event)
{
  if (focused)
    return;

  this->layoutPos = this->getLayoutPos();

  setStyleSheet("border:0px");
  QPropertyAnimation *colorAnimation = new QPropertyAnimation();
  colorAnimation->setTargetObject(this);
  colorAnimation->setPropertyName("color_B");
  colorAnimation->setDuration(300);

  colorAnimation->setKeyValueAt(0, 215);
  colorAnimation->setKeyValueAt(1, 255);
  colorAnimation->start();

  // setStyleSheet("background-color: rgb(231, 255, 255);");

  if (this->calendarMainWidget->rowStretch(this->layoutPos.y) > 10 || this->calendarMainWidget->columnStretch(this->layoutPos.x) > 10)
  {
    QPropertyAnimation *rowAnimation = new QPropertyAnimation();
    rowAnimation->setTargetObject(this);
    rowAnimation->setPropertyName("rowStr");
    rowAnimation->setDuration(80);

    rowAnimation->setKeyValueAt(0, this->calendarMainWidget->rowStretch(this->layoutPos.y));
    rowAnimation->setKeyValueAt(1, 10);

    QPropertyAnimation *colAnimation = new QPropertyAnimation();
    colAnimation->setTargetObject(this);
    colAnimation->setPropertyName("colStr");
    colAnimation->setDuration(80);

    colAnimation->setKeyValueAt(0, this->calendarMainWidget->columnStretch(this->layoutPos.x));
    colAnimation->setKeyValueAt(1, 10);

    rowAnimation->start();
    colAnimation->start();
  }
}

void CalendarCell::mousePressEvent(QMouseEvent *event)
{
  mouseClicked = true;
  this->layoutPos = this->getLayoutPos();

  if (focused && focused_x == this->layoutPos.x && focused_y == this->layoutPos.y)
  {
    // this->setText("cond 1\n" + QString::number(focused_x) + " " + QString::number(focused_y));
    focused = false;
    mouseClicked = false;
    focused_x = -1;
    focused_y = -1;
    if (this->calendarMainWidget->rowStretch(this->layoutPos.y) > 10 || this->calendarMainWidget->columnStretch(this->layoutPos.x) > 10)
    {
      QPropertyAnimation *rowAni = new QPropertyAnimation();
      rowAni->setTargetObject(this);
      rowAni->setPropertyName("rowStr");
      rowAni->setDuration(80);

      rowAni->setKeyValueAt(0, this->calendarMainWidget->rowStretch(this->layoutPos.y));
      rowAni->setKeyValueAt(1, 10);

      QPropertyAnimation *colAni = new QPropertyAnimation();
      colAni->setTargetObject(this);
      colAni->setPropertyName("colStr");
      colAni->setDuration(80);

      colAni->setKeyValueAt(0, this->calendarMainWidget->columnStretch(this->layoutPos.x));
      colAni->setKeyValueAt(1, 10);

      colAni->start();
      rowAni->start();
      connect(colAni, &QAbstractAnimation::finished, [=]()
              { 
                setStyleSheet("border:2px solid;"
                              "background-color: rgb(255, 214, 206);");
                return; });
    }
  }
  else if (focused)
  {
    // this->setText("cond 2\n" + QString::number(focused_x) + " " + QString::number(focused_y));

    CalendarCell *m_l = this->calendarMainWidget->parent()->findChild<CalendarCell *>(QString("L") + QString::number(focused_x) + QString("_") + QString::number(focused_y));
    m_l->setStyleSheet("border:0px;background-color: rgb(231, 255, 255)");
    m_l->mouseClicked = false;
    QPropertyAnimation *rowAni = new QPropertyAnimation();
    rowAni->setTargetObject(this);
    rowAni->setPropertyName("focusedRowStr");
    rowAni->setDuration(80);

    rowAni->setKeyValueAt(0, this->calendarMainWidget->rowStretch(focused_y));
    rowAni->setKeyValueAt(1, 10);

    QPropertyAnimation *colAni = new QPropertyAnimation();
    colAni->setTargetObject(this);
    colAni->setPropertyName("focusedColStr");
    colAni->setDuration(80);

    colAni->setKeyValueAt(0, this->calendarMainWidget->columnStretch(focused_x));
    colAni->setKeyValueAt(1, 10);

    connect(colAni, &QAbstractAnimation::finished, [=]()
            {
              focused_x = this->layoutPos.x;

              QPropertyAnimation *colAnimation = new QPropertyAnimation();
              colAnimation->setTargetObject(this);
              colAnimation->setPropertyName("colStr");
              colAnimation->setDuration(50);

              colAnimation->setKeyValueAt(0, this->calendarMainWidget->columnStretch(this->layoutPos.x));
              colAnimation->setKeyValueAt(1, 18);
              colAnimation->start(); });
    connect(rowAni, &QAbstractAnimation::finished, [=]()
            {
               focused_y = this->layoutPos.y;

              QPropertyAnimation *rowAnimation = new QPropertyAnimation();
              rowAnimation->setTargetObject(this);
              rowAnimation->setPropertyName("rowStr");
              rowAnimation->setDuration(50);

              rowAnimation->setKeyValueAt(0, this->calendarMainWidget->rowStretch(this->layoutPos.y));
              rowAnimation->setKeyValueAt(1, 18);
              rowAnimation->start(); });

    colAni->start();
    rowAni->start();

    setStyleSheet("border:2px solid;"
                  "background-color: rgb(255, 214, 206);");
    return;
  }
  else
  {
    // this->setText("cond 3\n" + QString::number(focused_x) + " " + QString::number(focused_y));
    focused = true;
    focused_x = this->layoutPos.x;
    focused_y = this->layoutPos.y;

    setStyleSheet("border:2px solid;"
                  "background-color: rgb(255, 214, 206);");

    QPropertyAnimation *rowAnimation = new QPropertyAnimation();
    rowAnimation->setTargetObject(this);
    rowAnimation->setPropertyName("rowStr");
    rowAnimation->setDuration(50);

    rowAnimation->setKeyValueAt(0, this->calendarMainWidget->rowStretch(this->layoutPos.y));
    rowAnimation->setKeyValueAt(1, 18);

    QPropertyAnimation *colAnimation = new QPropertyAnimation();
    colAnimation->setTargetObject(this);
    colAnimation->setPropertyName("colStr");
    colAnimation->setDuration(50);

    colAnimation->setKeyValueAt(0, this->calendarMainWidget->columnStretch(this->layoutPos.x));
    colAnimation->setKeyValueAt(1, 18);

    rowAnimation->start();
    colAnimation->start();

    // QFont font("Microsoft YaHei", 30, 75);
    // setFont(font);
  }
}

position CalendarCell::getLayoutPos()
{
  position m_pos;
  QString name = this->objectName();

  m_pos.x = name.mid(1, 1).toInt();
  m_pos.y = name.mid(3, 1).toInt();
  return m_pos;
}

int CalendarCell::rowStr() const
{
  return m_len;
}

void CalendarCell::setRowStr(const int len)
{
  m_len = len;
  this->calendarMainWidget->setRowStretch(this->layoutPos.y, m_len);
  // this->setText(QString::number(m_len));
}

int CalendarCell::colStr() const
{
  return m_wid;
}

void CalendarCell::setColStr(const int wid)
{
  m_wid = wid;
  this->calendarMainWidget->setColumnStretch(this->layoutPos.x, m_wid);
  // this->setText(QString::number(m_len));
}

int CalendarCell::focusedRowStr() const
{
  return m_focusedLen;
}

void CalendarCell::setFocusedRowStr(const int len)
{
  m_focusedLen = len;
  this->calendarMainWidget->setRowStretch(focused_y, m_focusedLen);
  // this->setText(QString::number(m_len));
}

int CalendarCell::focusedColStr() const
{
  return m_focusedWid;
}

void CalendarCell::setFocusedColStr(const int wid)
{
  m_focusedWid = wid;
  this->calendarMainWidget->setColumnStretch(focused_x, m_focusedWid);
}

int CalendarCell::color_B() const
{
  return m_color_B;
}

void CalendarCell::setColor_B(const int blue)
{
  m_color_B = blue;
  setStyleSheet("background-color: rgb(231, 255, " + QString::number(m_color_B) + ");");
}

NoteCell::NoteCell(QWidget *parent) : QWidget(parent)
{
  setStyleSheet("border:2px solid;"
                "background-color: rgb(100, 214, 206);");
  QGridLayout * noteCellMainLayout;


  noteCellMainLayout = new QGridLayout(this);
}

void NoteCell::setNoteInfo(noteInfo m_info)
{
  this->info.year = m_info.year;
  this->info.month = m_info.month;
  this->info.day = m_info.day;
  this->info.hour = m_info.hour;
  this->info.minute = m_info.minute;
  this->info.needAlarm = m_info.needAlarm;
  this->info.descryption = m_info.descryption;
  this->info.title = m_info.title;
}

NoteCell::~NoteCell()
{

}