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

private slots:
  void selectDatabase();
  void accepted();
  void smartStopSettingChanged(bool v);
  void smartStartSettingChanged(bool);
  void smartStopWayChanged();
  void allowStartAfterIdleControls();

};

#endif // PREFERENCESDLG_H
