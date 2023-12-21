#ifndef APPEVENTS_H
#define APPEVENTS_H

#include <QEvent>
#include "task.h"
enum
{
    ClientInitId        = 62000,
    ClientCloseId       = 62001,
    AttachDatabaseId    = 62002,
    SelectTaskId        = 62003,
    UiInitId            = 62004
};

class ClientEvent: public QEvent
{
private:
    int mType;
public:
    ClientEvent(int numtype)
        :QEvent(static_cast<QEvent::Type>(numtype)), mType(numtype)
    {}
};

class SelectTaskEvent: public ClientEvent
{
public:
    SelectTaskEvent(PTask task)
        :ClientEvent(SelectTaskId)
    {
        mTask = task;
    }

    PTask task() {
        return mTask;
    }

protected:
    PTask mTask;
};

#endif // APPEVENTS_H
