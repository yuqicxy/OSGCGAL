#pragma once
#include "osg/Callback"
#include "osg/Group"

class NodeAccessCallback: public osg::NodeCallback
{
public:
	enum Op
	{
		ADD,
		REMOVE,
		CLEAR
	};

	NodeAccessCallback(osg::Group* parent,Op oper);

	~NodeAccessCallback();

	virtual bool run(osg::Object* object, osg::Object* data);
	
	void setOpNode(osg::Node *node);

private:
	bool						mDirty;
	Op							mOpType;
	osg::ref_ptr<osg::Node>		mOpNode;
	osg::ref_ptr<osg::Group>	mRootNode;
};