#include "mainwindow.h"
#include <QApplication>
#include <QLayout>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.layout()->invalidate();

  w.setAttribute(Qt::WA_WState_ExplicitShowHide, false);
  w.setAttribute(Qt::WA_WState_Hidden, true);
  w.show();

  return a.exec();
}
