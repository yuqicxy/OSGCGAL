#pragma once
#include <osg/Node>
#include "QMetaType"

/*!
 * \class NodeIOBlock
 *
 * \brief NodeIOThread ���нڵ�д��д�������źŵ�����
 *
 * \author ����
 * \date ���� 2019
 */

class NodeIOBlock
{
public:
	NodeIOBlock();

	~NodeIOBlock();

	NodeIOBlock(const NodeIOBlock &other);

	osg::ref_ptr<osg::Node> GetNode();

	void SetNode(osg::ref_ptr<osg::Node>);

private:
	osg::ref_ptr<osg::Node> mNode;
};
Q_DECLARE_METATYPE(NodeIOBlock);