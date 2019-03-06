#include "Operation.h"
#include<osgDB/ReadFile>
#include<osgDB/WriteFile>

ReadNodeOperation::~ReadNodeOperation()
{
}

ReadNodeOperation::ReadNodeOperation(const ReadNodeOperation& other)
{
	mFileName = other.mFileName;
}

bool ReadNodeOperation::Operate()
{
	NodeIOBlock block;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(mFileName.toStdString());
	block.SetNode(node);
	emit ReadNodeFinished(block);
	return node.valid();
}

WriteNodeOperation::~WriteNodeOperation()
{
}

WriteNodeOperation::WriteNodeOperation(const WriteNodeOperation& other)
{
	mFileName = other.mFileName;
	mNode = other.mNode;
}

bool WriteNodeOperation::Operate()
{
	bool sucess = osgDB::writeNodeFile((*mNode), mFileName.toStdString());
	emit WriteNodeFinished(sucess);
	return sucess;
}