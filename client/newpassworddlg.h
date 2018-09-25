#ifndef NEWPASSWORDDLG_H
#define NEWPASSWORDDLG_H

#include <QDialog>

namespace Ui {
class NewPasswordDlg;
}

class NewPasswordDlg : public QDialog
{
  Q_OBJECT

public:
  explicit NewPasswordDlg(QWidget *parent = 0);
  ~NewPasswordDlg();
  QString password();

private:
  Ui::NewPasswordDlg *ui;

public slots:
  void tryAccept();
};

#endif // NEWPASSWORDDLG_H
