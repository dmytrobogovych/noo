#ifndef PASSWORDDLG_H
#define PASSWORDDLG_H

#include <QDialog>

namespace Ui {
class PasswordDlg;
}

class PasswordDlg : public QDialog
{
  Q_OBJECT

public:
  explicit PasswordDlg(QWidget *parent = 0);
  ~PasswordDlg();
  QString password();

private:
  Ui::PasswordDlg *ui;
};

#endif // PASSWORDDLG_H
