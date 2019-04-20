#pragma once
#include <osg/Node>
#include "QDockWidget"

class QTreeWidget;
class QTreeWidgetItem;

/*!
 * \class ProjectWidget
 *
 *	控制OSGCGAL根节点树的增删和显示隐藏
 *	
 * \brief 
 *
 * \author 余琦
 * \date 四月 2019
 */
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

	void RemoveItemByGUID(QString guid);

	osg::ref_ptr<osg::Node> FindNodeByGUID(const QString &name);

	QTreeWidgetItem* FindItemByGUID(const QString &name);

public Q_SLOTS:
	void PrepareMenu(const QPoint & pos);

	void itemClickedSLOT(QTreeWidgetItem *item, int column);

private:
	enum ItemType
	{
		ROOT,
		MODEL
	};

	QTreeWidget									*mTreeWidget;
	QTreeWidgetItem								*mRootItem;

	struct NodeItem
	{
		osg::ref_ptr<osg::Node> node;
		QTreeWidgetItem *item;
	};

	typedef std::map<QString, NodeItem>	 NodeItemMap;
	NodeItemMap mNameNodeItemMap;

private:
	const static int TypeRole = Qt::UserRole;
	const static int GUIDRole = Qt::UserRole + 1;
};