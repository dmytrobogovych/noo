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

template <int N>
class ClientEvent: public QEvent
{
private:
    int mType = N;
public:
    ClientEvent<N>()
        :QEvent(static_cast<QEvent::Type>(N))
    {}
};

class SelectTaskEvent: public ClientEvent<SelectTaskId>
{
public:
    SelectTaskEvent(PTask task) {
        mTask = task;
    }

    PTask task() {
        return mTask;
    }

protected:
    PTask mTask;
};

#endif // APPEVENTS_H
