#pragma once
#include "osg/Callback"
#include "osg/Group"

/*!
 * \class NodeAccessCallback
 *
 * \brief 线程安全的增删改查子节点
 *		  运行一次后自动析构
 *
 * \author 余琦
 * \date 三月 2019
 */
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