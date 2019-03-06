#pragma once
#include <osg/Node>
#include "QMetaType"

/*!
 * \class NodeIOBlock
 *
 * \brief NodeIOThread 运行节点写入写出发送信号的数据
 *
 * \author 余琦
 * \date 三月 2019
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