#pragma once
#include "osg/Callback"
#include "osg/Group"

/*!
 * \class NodeAccessCallback
 *
 * \brief �̰߳�ȫ����ɾ�Ĳ��ӽڵ�
 *		  ����һ�κ��Զ�����
 *
 * \author ����
 * \date ���� 2019
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