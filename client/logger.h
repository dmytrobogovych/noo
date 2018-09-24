#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
  Q_OBJECT
public:
  explicit Logger(QObject *parent = 0);
  ~Logger();

  void log(const char* msg);

protected:
  FILE* mFile;

  void open();
  void close();

signals:

public slots:

};

#endif // LOGGER_H
