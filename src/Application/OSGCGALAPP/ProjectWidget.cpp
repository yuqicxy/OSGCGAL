#include "ProjectWidget.h"
#include "QTreeWidget"
#include "QAction"
#include "QMenu"
#include "QDebug"
#include "QDockWidget"

#include "BuilderAction.h"
#include "Workbench.h"
#include "ViewerWidget.h"

ProjectWidget::ProjectWidget(QWidget *parent)
	:QDockWidget(parent)
{
	mTreeWidget = new QTreeWidget(parent);
	mTreeWidget->setHeaderHidden(true);
	
	mRootItem = new QTreeWidgetItem(QTreeWidgetItem::UserType);
	mRootItem->setText(0,tr("Root"));
	mRootItem->setData(0, Qt::UserRole, ItemType::ROOT);
	/*mNameNodeMap["Root"] = Workbench::getSingletonPtr()->GetViewerWidget()->GetRootNode();*/
	mNameNodeMap["Root"] = nullptr;

	mTreeWidget->addTopLevelItem(mRootItem);
	setWidget(mTreeWidget);
	
	mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(mTreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(PrepareMenu(const QPoint&)));
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
	item->setData(0, Qt::UserRole, MODEL);
	GetCurrentItem()->addChild(item);
	GetCurrentItem()->setExpanded(true);

	mNameNodeMap[name] = node;
}

void ProjectWidget::RemoveItem(QTreeWidgetItem *item)
{
	mNameNodeMap.erase(item->text(0));
	item->parent()->removeChild(item);
}

std::map<QString, osg::ref_ptr<osg::Node>> ProjectWidget::FindItemByName(const QString &name)
{
	QRegExp reg(QString("^") + name);
	std::map<QString,osg::ref_ptr<osg::Node>> map;
	for (std::map<QString,osg::ref_ptr<osg::Node>>::const_iterator itr = mNameNodeMap.begin();
		itr != mNameNodeMap.cend(); ++itr)
	{
		if (reg.exactMatch(itr->first))
		{
			map[itr->first]= itr->second;
		}
	}
	return map;
}

void ProjectWidget::PrepareMenu(const QPoint & pos)
{
	QTreeWidgetItem *item = mTreeWidget->itemAt(pos);

	if (item == nullptr)
		return;

	mTreeWidget->setCurrentItem(item);

	QMenu menu(this);
	switch (item->data(0,Qt::UserRole).toUInt())
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
