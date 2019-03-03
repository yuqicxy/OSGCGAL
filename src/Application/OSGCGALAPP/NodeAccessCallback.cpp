#include "NodeAccessCallback.h"

NodeAccessCallback::NodeAccessCallback(osg::Group* parent, Op oper)
	:mRootNode(parent)
	,mOpType(oper)
	,mDirty(false)
{
}

NodeAccessCallback::~NodeAccessCallback()
{
}

bool NodeAccessCallback::run(osg::Object* object, osg::Object* data)
{
	if (mDirty)
	{
		mRootNode->removeUpdateCallback(this);
		return true;
	}
	if (object == mRootNode.get() && !mDirty)
	{
		switch (mOpType)
		{
			case ADD:
			{
				if(mOpNode.valid())
					mRootNode->addChild(mOpNode);
				break;
			}
			case REMOVE:
			{
				if (mOpNode.valid())
					mRootNode->removeChild(mOpNode);
				break;
			}
			case CLEAR:
			{
				mRootNode->removeChildren(0, mRootNode->getNumChildren());
				break;
			}
		}
		mDirty = true;
	}
	return osg::NodeCallback::run(object, data);
}

void NodeAccessCallback::setOpNode(osg::Node *node)
{
	mOpNode = node;
}