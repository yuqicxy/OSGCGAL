#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/viewer>

int main()
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("F:\\OpenSceneGraph\\Data\\cow.osg");\
		osgViewer::Viewer viewer;
	viewer.setSceneData(node);
	return viewer.run();
}