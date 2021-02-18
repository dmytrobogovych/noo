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

#define GET_BOOL(KEY) settings.data().value(KEY).toBool()

PreferencesDlg::PreferencesDlg(QWidget *parent, Settings& settings) :
    QDialog(parent, Qt::Sheet),
    ui(new Ui::PreferencesDlg),
    mSettings(settings)
{
    ui->setupUi(this);
    connect(ui->mSelectDatabaseButton, SIGNAL(clicked()), this, SLOT(selectDatabase()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(ui->mSmartStopTracking, SIGNAL(toggled(bool)), this, SLOT(smartStopSettingChanged(bool)));
    connect(ui->mSmartStartTracking, SIGNAL(toggled(bool)), this, SLOT(smartStartSettingChanged(bool)));

    // Autosave password
    ui->mAutosavePasswordCheckbox->setChecked(settings.data().value(KEY_AUTOSAVE_PASSWORD).toBool());

    // Show seconds or not?
    ui->mShowSecondsCheckbox->setChecked(settings.data().value(KEY_SHOW_SECONDS).toBool());

    // Ask confirmation before node delete
    ui->mAskBeforeDeleteCheckbox->setChecked(settings.data().value(KEY_ASK_BEFORE_DELETE).toBool());

    // Dark theme ?
    ui->mDarkThemeCheckbox->setChecked(settings.data().value(KEY_DARK_THEME).toBool());

    // Use custom database path ?
    ui->mDatabaseLocation->setText(settings.data().value(KEY_DB_FILENAME).toString());

    // Use stop on idle ?
    ui->mSmartStopTracking->setChecked(GET_BOOL(KEY_SMART_STOP));
    ui->mSmartStopIntervalInMinutes->setText(settings.data().value(KEY_SMART_STOP_MINUTES).toString());
    ui->mAskQuestionOnStopRadiobutton->setChecked(GET_BOOL(KEY_ASK_STOP));
    ui->mAutomaticallyOnStopRadiobutton->setChecked(!GET_BOOL(KEY_ASK_STOP));

    // Use start after idle ?
    ui->mSmartStartTracking->setChecked(GET_BOOL(KEY_SMART_START));
    //ui->mAskQuestionOnStartRadiobutton->setChecked(GET_BOOL(KEY_ASK_START));
    //ui->mAutomaticallyOnStartRadiobutton->setChecked(!GET_BOOL(KEY_ASK_START));

    allowStartAfterIdleControls();

    ui->mShowTrayIconCheckbox->setChecked(GET_BOOL(KEY_SHOW_TRAY_ICON));
}


PreferencesDlg::~PreferencesDlg()
{
    delete ui;
}

void PreferencesDlg::selectDatabase()
{
    QFileDialog dlg(this, tr("Select database to use"), helper::path::pathToDesktop());
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setFileMode(QFileDialog::AnyFile);
    if (dlg.exec() == QDialog::Accepted)
    {
        QString filename = dlg.selectedFiles().front();
        ui->mDatabaseLocation->setText(filename);
    }
}

void PreferencesDlg::accepted()
{
    bool savePassword = ui->mAutosavePasswordCheckbox->isChecked();
    mSettings.data()[KEY_AUTOSAVE_PASSWORD] = savePassword;
    helper::password::save(savePassword ? Storage::instance().key() : QString(""));

    mSettings.data()[KEY_SHOW_SECONDS] = ui->mShowSecondsCheckbox->isChecked();
    mSettings.data()[KEY_ASK_BEFORE_DELETE] = ui->mAskBeforeDeleteCheckbox->isChecked();
    mSettings.data()[KEY_DB_FILENAME] = ui->mDatabaseLocation->text();
    mSettings.data()[KEY_SMART_STOP] = ui->mSmartStopTracking->isChecked();
    mSettings.data()[KEY_SMART_STOP_MINUTES] = ui->mSmartStopIntervalInMinutes->text().toInt();
    mSettings.data()[KEY_SMART_START] = ui->mSmartStartTracking->isChecked();
    mSettings.data()[KEY_SHOW_TRAY_ICON] = ui->mShowTrayIconCheckbox->isChecked();
    mSettings.data()[KEY_ASK_STOP] = ui->mAskQuestionOnStopRadiobutton->isChecked();

    if (mSettings.data()[KEY_DARK_THEME].toBool() != ui->mDarkThemeCheckbox->isChecked()) {
        mSettings.data()[KEY_DARK_THEME] = ui->mDarkThemeCheckbox->isChecked();
        applyTheme();
    }
}


void PreferencesDlg::smartStopSettingChanged(bool v)
{
    if (v)
    {
        if (!helper::activityTracker::ensureSmartTrackingIsPossible())
            ui->mSmartStopTracking->setChecked(false);
    }
    allowStartAfterIdleControls();
}

void PreferencesDlg::smartStartSettingChanged(bool/* v */)
{
    allowStartAfterIdleControls();
}

void PreferencesDlg::smartStopWayChanged()
{
    allowStartAfterIdleControls();
}

void PreferencesDlg::allowStartAfterIdleControls()
{
    bool stopEnabled = ui->mSmartStopTracking->isChecked() && ui->mSmartStopIntervalInMinutes->text().toInt() > 0;
    bool startEnabled = ui->mSmartStartTracking->isChecked();
    bool automaticStopEnabled = ui->mAutomaticallyOnStopRadiobutton->isChecked();
    //ui->mAskQuestionOnStartRadiobutton->setEnabled(stopEnabled && startEnabled);
    //ui->mAutomaticallyOnStartRadiobutton->setEnabled(stopEnabled && startEnabled);
    if (!stopEnabled || !automaticStopEnabled)
        ui->mSmartStartTracking->setChecked(false);
    ui->mSmartStartTracking->setEnabled(stopEnabled && automaticStopEnabled);
    ui->mAskQuestionOnStopRadiobutton->setEnabled(stopEnabled);
    ui->mAutomaticallyOnStopRadiobutton->setEnabled(stopEnabled);
}

void PreferencesDlg::applyTheme()
{
    helper::theme::applyCurrent(mSettings);
}
