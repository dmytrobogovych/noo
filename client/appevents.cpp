#include "appevents.h"

ClientInitEvent::ClientInitEvent()
  :QEvent(static_cast<Type>(ClientInitId))
{
}

ClientCloseEvent::ClientCloseEvent()
  :QEvent(static_cast<Type>(ClientCloseId))
{}

AttachDatabaseEvent::AttachDatabaseEvent()
  :QEvent(static_cast<Type>(AttachDatabaseId))
{}

SelectTaskEvent::SelectTaskEvent(PTask task)
  :QEvent(static_cast<Type>(SelectTaskId)), mTask(task)
{}

PTask SelectTaskEvent::task()
{
  return mTask;
}

UiInitEvent::UiInitEvent()
    :QEvent(static_cast<Type>(UiInitId))
{}
