#include "stdafx.h"
#include "osgQtWidget.h"
#include "osgQtWidgetPlugin.h"

#include <QtCore/QtPlugin>

osgQtWidgetPlugin::osgQtWidgetPlugin(QObject *parent)
	: QObject(parent)
{
	initialized = false;
}

void osgQtWidgetPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
	if (initialized)
		return;

	initialized = true;
}

bool osgQtWidgetPlugin::isInitialized() const
{
	return initialized;
}

QWidget *osgQtWidgetPlugin::createWidget(QWidget *parent)
{
	return new osgQtWidget(parent);
}

QString osgQtWidgetPlugin::name() const
{
	return "osgQtWidget";
}

QString osgQtWidgetPlugin::group() const
{
	return "osgQtWidgetPlugin";
}

QIcon osgQtWidgetPlugin::icon() const
{
	return QIcon();
}

QString osgQtWidgetPlugin::toolTip() const
{
	return QString(tr("Osg Qt Widget"));
}

QString osgQtWidgetPlugin::whatsThis() const
{
	return QString(tr("osg bing qt widget"));
}

bool osgQtWidgetPlugin::isContainer() const
{
	return false;
}

QString osgQtWidgetPlugin::domXml() const
{
	return "<widget class=\"osgQtWidget\" name=\"osgQtWidget\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>100</height>\n"
		"  </rect>\n"
		" </property>\n"
		"</widget>\n";
}

QString osgQtWidgetPlugin::includeFile() const
{
	return "osgQtWidget.h";
}
