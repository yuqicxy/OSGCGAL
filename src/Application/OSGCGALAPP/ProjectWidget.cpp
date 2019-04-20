#include "ProjectWidget.h"
#include "QTreeWidget"
#include "QAction"
#include "QMenu"
#include "QDebug"
#include "QDockWidget"

#include "BuilderAction.h"
#include "Workbench.h"
#include "ViewerWidget.h"

#include "CGALUtility.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	:QDockWidget(parent)
{
	mTreeWidget = new QTreeWidget(parent);
	mTreeWidget->setHeaderHidden(true);
	
	mRootItem = new QTreeWidgetItem(QTreeWidgetItem::UserType);
	mRootItem->setText(0,tr("Root"));
	mRootItem->setData(0, Qt::UserRole, ItemType::ROOT);
	/*mNameNodeMap["Root"] = Workbench::getSingletonPtr()->GetViewerWidget()->GetRootNode();*/
	//mNameNodeItemMap["Root"] = nullptr;

	mTreeWidget->addTopLevelItem(mRootItem);
	setWidget(mTreeWidget);
	
	mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(mTreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(PrepareMenu(const QPoint&)));

	connect(mTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *item, int column)),
		this, SLOT(itemClickedSLOT(QTreeWidgetItem *item, int column)));
}

ProjectWidget::~ProjectWidget()
{
}

QTreeWidgetItem *ProjectWidget::GetCurrentItem()
{
	return mTreeWidget->currentItem();
}

void ProjectWidget::AddModelItem(const QString& name,
	osg::ref_ptr<osg::Node> node,
	const QString &statusTip /*= QString::null*/)
{
	QTreeWidgetItem *item = new QTreeWidgetItem;
	item->setStatusTip(0,statusTip);
	item->setToolTip(0, statusTip);
	item->setText(0, name);
	item->setData(0, TypeRole, MODEL);
	QString guid = QString::fromLocal8Bit(GenerateGUID().c_str());
	item->setData(0, GUIDRole, guid);
	GetCurrentItem()->addChild(item);
	GetCurrentItem()->setExpanded(true);

	Workbench::getSingletonPtr()->GetViewerWidget()->addChild(node);
	NodeItem nodeitem{ node,item };
	mNameNodeItemMap[guid] = nodeitem;
}

void ProjectWidget::RemoveItem(QTreeWidgetItem *item)
{
	NodeItemMap::const_iterator itr;
	itr = mNameNodeItemMap.find(item->data(0, GUIDRole).toString());
	if (itr != mNameNodeItemMap.end())
	{
		Workbench::getSingletonPtr()->GetViewerWidget()->removeChild(itr->second.node);
		item->parent()->removeChild(item);
		mNameNodeItemMap.erase(itr);
	}
}

void ProjectWidget::RemoveItemByGUID(QString guid)
{
	QTreeWidgetItem *item = FindItemByGUID(guid);
	if (item != nullptr)
	{
		RemoveItem(item);
	}
}

osg::ref_ptr<osg::Node> ProjectWidget::FindNodeByGUID(const QString &guid)
{
	NodeItemMap::const_iterator itr;
	itr = mNameNodeItemMap.find(guid);
	if (itr != mNameNodeItemMap.cend())
	{
		return itr->second.node;
	}
	return nullptr;
}

QTreeWidgetItem* ProjectWidget::FindItemByGUID(const QString &guid)
{
	NodeItemMap::const_iterator itr;
	itr = mNameNodeItemMap.find(guid);
	if (itr != mNameNodeItemMap.cend())
	{
		return itr->second.item;
	}
	return nullptr;
}

void ProjectWidget::PrepareMenu(const QPoint & pos)
{
	QTreeWidgetItem *item = mTreeWidget->itemAt(pos);

	if (item == nullptr)
		return;

	mTreeWidget->setCurrentItem(item);

	QMenu menu(this);
	switch (item->data(0,TypeRole).toUInt())
	{
	case ItemType::ROOT:
		menu.addAction(BuilderAction::getSingleton().mOpenModelAction);
		menu.addAction(BuilderAction::getSingleton().mAddObliqueDataAction);
		break;
	case ItemType::MODEL:
		menu.addAction(BuilderAction::getSingleton().mRemoveModelAction);
		break;
	default:
		break;
	}

	QPoint pt(pos);
	menu.exec(mTreeWidget->mapToGlobal(pos));
}

void ProjectWidget::itemClickedSLOT(QTreeWidgetItem *item, int column)
{
}