#include "NodeIOThread.h"
#include "Operation.h"

NodeIOThread::NodeIOThread(QObject *parent)
	:QThread(parent)
	, mStop(false)
{
}

NodeIOThread::~NodeIOThread()
{
	mMutex.lock();
	mStop = true;
	mMutex.unlock();

	wait();
}

void NodeIOThread::Stop()
{
	mMutex.lock();
	mStop = true;
	mMutex.unlock();
}

void NodeIOThread::run()
{
	while (!mStop)
	{
		Operation *oper = mOperationQueue.takeFirst();
		if (oper != nullptr)
			oper->Operate();
	}
}