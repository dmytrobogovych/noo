#ifndef ATTACHMENTSDIALOG_H
#define ATTACHMENTSDIALOG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class AttachmentsDialog;
}

class AttachmentsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AttachmentsDialog(PTask task, QWidget *parent = 0);
  ~AttachmentsDialog();

private:
  Ui::AttachmentsDialog *ui;
};

#endif // ATTACHMENTSDIALOG_H
