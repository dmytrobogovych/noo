#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "findsupport.h"

namespace Ui {
class FindDialog;
}

class FindInTasksDialog : public QDialog
{
  Q_OBJECT

public:
  explicit FindInTasksDialog(QWidget *parent = 0);
  ~FindInTasksDialog();

  FindResultItem& getResult();

public slots:
  void startSearch();
  void resultSelected(const QModelIndex& index);
  void searchComplete();
  void onNewResult(const FindResultItem& item);
private:
  Ui::FindDialog *ui;
  FindResultsModel* mModel;
  TaskSearch mSearchHelper;
  FindResultItem mResult;
};

#endif // FINDDIALOG_H
