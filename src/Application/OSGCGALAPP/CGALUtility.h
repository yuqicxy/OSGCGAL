#pragma once
#include <strstream>
#include"osg/Node"

namespace OSGCGAL
{
	//************************************
	// Method:    GenerateGUID
	// FullName:  GenerateGUID
	// Access:    public 
	// Returns:   extern std
	// Qualifier: Éú³ÉGUID
	//************************************
	extern  std::string GenerateGUID();

	extern osg::ref_ptr<osg::Node> ReadNodeFile(std::string fileName);
}

