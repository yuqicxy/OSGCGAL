#include "CGALUtility.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"

#include <osgDB/ReadFile>
#include <osg/Notify>

namespace OSGCGAL
{
	std::string GenerateGUID()
	{
		boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
		std::string uuid_string = boost::uuids::to_string(a_uuid);
		return uuid_string;
	}

	osg::ref_ptr<osg::Node> ReadNodeFile(std::string fileName)
	{
		try
		{
			return osgDB::readNodeFile(fileName);
		}
		catch (...)
		{
			osg::notify(osg::FATAL) << "Failed to Open" << fileName << std::endl;
			return nullptr;
		}
	}

}

