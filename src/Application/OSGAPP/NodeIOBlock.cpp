#include "NodeIOBlock.h"

NodeIOBlock::NodeIOBlock()
	:mNode(nullptr)
{
}

NodeIOBlock::~NodeIOBlock()
{
}

NodeIOBlock::NodeIOBlock(const NodeIOBlock &other)
{
	mNode = other.mNode;
}

osg::ref_ptr<osg::Node> NodeIOBlock::GetNode()
{
	return mNode;
}

void NodeIOBlock::SetNode(osg::ref_ptr<osg::Node> node)
{
	mNode = node;
}