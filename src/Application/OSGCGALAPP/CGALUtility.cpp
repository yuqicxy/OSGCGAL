#include "CGALUtility.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"

std::string GenerateGUID()
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	std::string uuid_string = boost::uuids::to_string(a_uuid);
	return uuid_string;
}
