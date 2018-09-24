#include "fvupdatewindow.h"
#include "ui_fvupdatewindow.h"
#include "fvupdater.h"
#include "fvavailableupdate.h"
#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>

FvUpdateWindow::FvUpdateWindow(QWidget *parent) :
	QWidget(parent),
  m_ui(new Ui::FvUpdateWindow), m_NetworkReply(nullptr)
{
	m_ui->setupUi(this);

	// Delete on close
	setAttribute(Qt::WA_DeleteOnClose, true);

	// Set the "new version is available" string
	QString newVersString = m_ui->newVersionIsAvailableLabel->text().arg(QString::fromUtf8(FV_APP_NAME));
	m_ui->newVersionIsAvailableLabel->setText(newVersString);

	// Connect buttons
	connect(m_ui->installUpdateButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(InstallUpdate()));
	connect(m_ui->skipThisVersionButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(SkipUpdate()));
	connect(m_ui->remindMeLaterButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(RemindMeLater()));

  connect(&m_Network, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

FvUpdateWindow::~FvUpdateWindow()
{
	delete m_ui;
}

bool FvUpdateWindow::UpdateWindowWithCurrentProposedUpdate()
{
	FvAvailableUpdate* proposedUpdate = FvUpdater::sharedUpdater()->GetProposedUpdate();
	if (! proposedUpdate) {
		return false;
	}

	QString downloadString = m_ui->wouldYouLikeToDownloadLabel->text()
			.arg(QString::fromUtf8(FV_APP_NAME), proposedUpdate->GetEnclosureVersion(), QString::fromUtf8(FV_APP_VERSION));
	m_ui->wouldYouLikeToDownloadLabel->setText(downloadString);

  QUrl notesUrl = proposedUpdate->GetReleaseNotesLink();
  m_NetworkReply = m_Network.get(QNetworkRequest(notesUrl));

	return true;
}

void FvUpdateWindow::closeEvent(QCloseEvent* event)
{
	FvUpdater::sharedUpdater()->updaterWindowWasClosed();
  if (m_NetworkReply)
    m_NetworkReply->abort();

  event->accept();
}

void FvUpdateWindow::downloadFinished(QNetworkReply *reply)
{
  if (reply->error() == QNetworkReply::NoError)
    m_ui->releaseNotes->setText(QString(reply->readAll()));

  reply->deleteLater();
  m_NetworkReply = nullptr;
}
