#include "string.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace userver::formats::parse
{
boost::uuids::uuid Parse(const std::string& value,
                         userver::formats::parse::To<boost::uuids::uuid>)
{
    return boost::lexical_cast<boost::uuids::uuid>(value);
}
}  // namespace userver::formats::parse
