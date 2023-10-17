#include "string.hpp"

#include <boost/uuid/uuid_io.hpp>

namespace userver::formats::serialize
{
std::string Serialize(const boost::uuids::uuid& value,
                      userver::formats::serialize::To<std::string>)
{
    return to_string(value);
}
}  // namespace userver::formats::serialize
