#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>
#include <userver/formats/serialize/to.hpp>
namespace userver::formats::serialize
{
std::string Serialize(const boost::uuids::uuid& value,
                      userver::formats::serialize::To<std::string>);
}
