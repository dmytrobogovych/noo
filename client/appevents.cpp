#include "appevents.h"

ClientInitEvent::ClientInitEvent()
  :QEvent((Type)ClientInitId)
{
}

ClientCloseEvent::ClientCloseEvent()
  :QEvent((Type)ClientCloseId)
{}

AttachDatabaseEvent::AttachDatabaseEvent()
  :QEvent((Type)AttachDatabaseId)
{}

SelectTaskEvent::SelectTaskEvent(PTask task)
  :QEvent((Type)SelectTaskId), mTask(task)
{}

PTask SelectTaskEvent::task()
{
  return mTask;
}
