#include "passworddlg.h"
#include "ui_passworddlg.h"

PasswordDlg::PasswordDlg(QWidget *parent) :
  QDialog(parent, Qt::Sheet),
  ui(new Ui::PasswordDlg)
{
  ui->setupUi(this);

  // TODO
  /*
   myLabel->setText("<a href=\"http://example.com/\">Click Here!</a>");
  myLabel->setTextFormat(Qt::RichText);
  myLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  myLabel->setOpenExternalLinks(true);
  */
}

PasswordDlg::~PasswordDlg()
{
  delete ui;
}

QString PasswordDlg::password()
{
  return ui->mPasswordEdit->text();
}
