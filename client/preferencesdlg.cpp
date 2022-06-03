#include "preferencesdlg.h"
#include "ui_preferencesdlg.h"
#include "settings.h"
#include "helper.h"
#include "storage.h"
#include "platforms/hidtracker.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSysInfo>
#include <QTextStream>
#include <QFontDialog>

#define GET_BOOL(KEY) settings.data().value(KEY).toBool()

PreferencesDlg::PreferencesDlg(QWidget *parent, Settings& settings) :
    QDialog(parent, Qt::Sheet),
    ui(new Ui::PreferencesDlg),
    mSettings(settings)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));

    connect(ui->mChangePathButton, SIGNAL(clicked()), this, SLOT(onChangeDatabasePath()));
    connect(ui->mPauseOnIdleCheckbox, SIGNAL(toggled(bool)), this, SLOT(onPauseOnIdle(bool)));
    connect(ui->mChangeAppFontButton, SIGNAL(clicked()), this, SLOT(onChangeAppFont()));

    // Autosave password
    ui->mAutosavePasswordCheckbox->setChecked(settings.data().value(KEY_AUTOSAVE_PASSWORD).toBool());

    // Show seconds or not?
    ui->mShowSecondsCheckbox->setChecked(settings.data().value(KEY_SHOW_SECONDS).toBool());

    // Ask confirmation before node delete
    ui->mAskBeforeDeleteCheckbox->setChecked(settings.data().value(KEY_ASK_BEFORE_DELETE).toBool());

    // Dark theme ?
    ui->mDarkThemeCheckbox->setChecked(settings.data().value(KEY_DARK_THEME).toBool());

    // Use custom database path ?
    ui->mPathToDatabaseLabel->setText(settings.data().value(KEY_DB_FILENAME).toString());

    // Use stop on idle ?
    ui->mPauseOnIdleCheckbox->setChecked(GET_BOOL(KEY_SMART_STOP));
    ui->mIdleTimeoutEdit->setText(settings.data().value(KEY_SMART_STOP_MINUTES).toString());
    ui->mAskQuestionOnResumeCheckbox->setChecked(GET_BOOL(KEY_ASK_STOP));

    ui->mShowTrayIconCheckbox->setChecked(GET_BOOL(KEY_SHOW_TRAY_ICON));

    QFont f = qApp->font();
    ui->mAppFontLabel->setText(QString("%1 %2pt").arg(f.family()).arg(f.pointSize()));
    ui->mAppFontLabel->setFont(f);
}


PreferencesDlg::~PreferencesDlg()
{
    delete ui;
}

void PreferencesDlg::onChangeDatabasePath()
{
    QFileDialog dlg(this, tr("Select database to use"), helper::path::pathToDesktop());
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setFileMode(QFileDialog::AnyFile);
    if (dlg.exec() == QDialog::Accepted)
    {
        QString filename = dlg.selectedFiles().front();
        ui->mPathToDatabaseLabel->setText(filename);
    }
}

void PreferencesDlg::onPauseOnIdle(bool value)
{
    if (value)
    {
        // It is possible to check idle time at all ?
        if (!helper::activityTracker::ensureSmartTrackingIsPossible())
            ui->mPauseOnIdleCheckbox->setChecked(false);
    }
}

void PreferencesDlg::onChangeAppFont()
{
    QFontDialog dlg;
    dlg.setCurrentFont(qApp->font());
    if (dlg.exec() == QDialog::Accepted)
    {
        QFont f = dlg.currentFont();
        ui->mAppFontLabel->setText(QString("%1 %2pt").arg(f.family()).arg(f.pointSize()));
        ui->mAppFontLabel->setFont(f);
    }
}

void PreferencesDlg::accepted()
{
    bool savePassword = ui->mAutosavePasswordCheckbox->isChecked();
    mSettings.data()[KEY_AUTOSAVE_PASSWORD] = savePassword;
    helper::password::saveToKeychain(savePassword ? Storage::instance().key() : QString(""));

    mSettings.data()[KEY_SHOW_SECONDS] = ui->mShowSecondsCheckbox->isChecked();
    mSettings.data()[KEY_ASK_BEFORE_DELETE] = ui->mAskBeforeDeleteCheckbox->isChecked();
    mSettings.data()[KEY_DB_FILENAME] = ui->mPathToDatabaseLabel->text();
    mSettings.data()[KEY_SMART_STOP] = ui->mPauseOnIdleCheckbox->isChecked();
    mSettings.data()[KEY_SMART_STOP_MINUTES] = ui->mIdleTimeoutEdit->text().toInt();
    mSettings.data()[KEY_SHOW_TRAY_ICON] = ui->mShowTrayIconCheckbox->isChecked();
    mSettings.data()[KEY_ASK_STOP] = ui->mAskQuestionOnResumeCheckbox->isChecked();

    if (mSettings.data()[KEY_DARK_THEME].toBool() != ui->mDarkThemeCheckbox->isChecked()) {
        mSettings.data()[KEY_DARK_THEME] = ui->mDarkThemeCheckbox->isChecked();
        helper::theme::applyCurrent(mSettings);
    }

    mSettings.data()[KEY_APP_FONT] = ui->mAppFontLabel->font().toString();
    mSettings.save();
}

void PreferencesDlg::rejected()
{
}
