#include "kdispatch.h"

KDispatch::KDispatch(TaskInfoStru task, BaseDevice *device)
{
    this->m_task = task;
    this->m_pBase = device;
}

void KDispatch::testfunction()
{

}
