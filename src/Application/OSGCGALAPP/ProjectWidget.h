#pragma once
#include <osg/Node>
#include "QDockWidget"

class QTreeWidget;
class QTreeWidgetItem;

class ProjectWidget : public QDockWidget
{
	Q_OBJECT
public:
	ProjectWidget(QWidget *parent);

	~ProjectWidget();

	QTreeWidgetItem *GetCurrentItem();

	void AddModelItem(const QString& name,
		osg::ref_ptr<osg::Node> node,
		const QString &StatsTip = QString::null);
	
	void RemoveItem(QTreeWidgetItem *item);

	std::map<QString, osg::ref_ptr<osg::Node>> FindItemByName(const QString &name);

public Q_SLOTS:
	void PrepareMenu(const QPoint & pos);

private:
	enum ItemType
	{
		ROOT,
		MODEL
	};

	QTreeWidget									*mTreeWidget;
	QTreeWidgetItem								*mRootItem;
	std::map<QString, osg::ref_ptr<osg::Node>>	mNameNodeMap;
};