#pragma once
#include "QThread"
#include "QMutex"
#include "QQueue"

class NodeIOBlock;
class Operation;
class NodeIOThread : public QThread
{
	Q_OBJECT
public:
	NodeIOThread(QObject *parent);
	
	~NodeIOThread();

public Q_SLOTS:
	void Stop();

protected:
	virtual void run();

private:
	bool				mStop;
	QMutex				mMutex;
	QQueue<Operation*>	mOperationQueue;
};