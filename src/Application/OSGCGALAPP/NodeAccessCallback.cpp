#include "NodeAccessCallback.h"

NodeAccessCallback::NodeAccessCallback(osg::Group* parent, Op oper)
	:mRootNode(parent)
	,mOpType(oper)
{
}

NodeAccessCallback::~NodeAccessCallback()
{
}

bool NodeAccessCallback::run(osg::Object* object, osg::Object* data)
{
	if (object == mRootNode.get())
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
	}
	bool val = osg::NodeCallback::run(object, data);
	//remove callback from parent
	mRootNode->removeUpdateCallback(this);
	return val;
}

void NodeAccessCallback::setOpNode(osg::Node *node)
{
	mOpNode = node;
}