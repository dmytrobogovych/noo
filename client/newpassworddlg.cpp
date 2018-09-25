#include "newpassworddlg.h"
#include "ui_newpassworddlg.h"
#include <QMessageBox>

NewPasswordDlg::NewPasswordDlg(QWidget *parent) :
  QDialog(parent, Qt::Sheet),
  ui(new Ui::NewPasswordDlg)
{
  ui->setupUi(this);
}

NewPasswordDlg::~NewPasswordDlg()
{
  delete ui;
}

QString NewPasswordDlg::password()
{
  return ui->mNewPasswordEdit1->text();
}

void NewPasswordDlg::tryAccept()
{
  if (ui->mNewPasswordEdit1->text() != ui->mNewPasswordEdit2->text())
  {
    QMessageBox::warning(this, tr("Error"), tr("Passwords do not match"), "Ok");
    return;
  }
  accept();
}
