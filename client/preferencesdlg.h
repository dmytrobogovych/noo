#ifndef PREFERENCESDLG_H
#define PREFERENCESDLG_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class PreferencesDlg;
}

class PreferencesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDlg(QWidget *parent, Settings& settings);
    ~PreferencesDlg();

private:
    Ui::PreferencesDlg *ui;
    Settings& mSettings;

    void applyTheme();

private slots:
    void accepted();
    void rejected();

    void onPauseOnIdle(bool v);
    void onChangeAppFont();
    void onChangeDatabasePath();
};

#endif // PREFERENCESDLG_H
