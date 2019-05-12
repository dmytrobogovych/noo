#ifndef APPEVENTS_H
#define APPEVENTS_H

#include <QEvent>
#include "task.h"
enum
{
    ClientInitId = 62000,
    ClientCloseId = 62001,
    AttachDatabaseId,
    SelectTaskId,
    UiInitId
};

class ClientInitEvent: public QEvent
{
public:
    ClientInitEvent();
};

class ClientCloseEvent: public QEvent
{
public:
    ClientCloseEvent();
};

class AttachDatabaseEvent: public QEvent
{
public:
    AttachDatabaseEvent();
};

class SelectTaskEvent: public QEvent
{
public:
    SelectTaskEvent(PTask task);
    PTask task();

protected:
    PTask mTask;
};

class UiInitEvent: public QEvent
{
public:
    UiInitEvent();
};


#endif // APPEVENTS_H
