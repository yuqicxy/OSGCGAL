#pragma once
#include "QObject"
#include "QString"
#include <osg/Node>
#include "NodeIOBlock.h"

class NodeIOBlock;
class Operation : public QObject
{
public:
	Operation(QObject *parent = nullptr):QObject(parent){}
	
	virtual ~Operation(){}

	Operation(const Operation&){}

	virtual bool Operate() = 0;
};

class ReadNodeOperation:public Operation
{
	Q_OBJECT
public:
	ReadNodeOperation(const QString &nodeFileName,QObject *parent = nullptr)
		:mFileName(nodeFileName)
		,Operation(parent)
	{}

	virtual ~ReadNodeOperation();

	ReadNodeOperation(const ReadNodeOperation& other);

	virtual bool Operate();

Q_SIGNALS:
	void ReadNodeFinished(const NodeIOBlock data);

private:
	QString mFileName;
};

class WriteNodeOperation : public Operation
{
	Q_OBJECT
public:
	WriteNodeOperation(osg::ref_ptr<osg::Node> node,const QString &nodeFileName, QObject *parent = nullptr)
		:Operation(parent)
		, mFileName(nodeFileName)
		, mNode(node)
	{}

	virtual ~WriteNodeOperation();

	WriteNodeOperation(const WriteNodeOperation& other);

	virtual bool Operate();

Q_SIGNALS:
	void  WriteNodeFinished(bool);

private:
	QString					mFileName;
	osg::ref_ptr<osg::Node> mNode;
};