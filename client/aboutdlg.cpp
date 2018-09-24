#include "config.h"
#include "aboutdlg.h"
#include "ui_aboutdlg.h"
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

AboutDlg::AboutDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AboutDlg)
{
  ui->setupUi(this);

  //QPushButton* btn = ui->mButtonBox->addButton(tr("License"), QDialogButtonBox::AcceptRole);
  //this->connect(btn, SIGNAL(clicked()), this, SLOT(showLicense()));

  QString text(ABOUTTEXT);
  text += ".\r\n";
  text += QString("Version %1.").arg(VER);
  ui->mTextLabel->setText(text);

  QString appPath = QCoreApplication::applicationDirPath();
  appPath += "/../Resources/License.rtf";
  ui->mLicenseLabel->setText("<a href=\"" + QUrl::fromLocalFile(appPath).toString() + "\">License</a>");
  ui->mLicenseLabel->setTextFormat(Qt::RichText);
  ui->mLicenseLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  ui->mLicenseLabel->setOpenExternalLinks(true);
  setWindowTitle(APPNAME);
}

AboutDlg::~AboutDlg()
{
  delete ui;
}

void AboutDlg::showLicense()
{
#ifdef TARGET_OSX
    QString appPath = QCoreApplication::applicationDirPath();
    appPath += "/../Resources/License.rtf";
    QDesktopServices::openUrl(QUrl::fromLocalFile(appPath));
#endif
}
