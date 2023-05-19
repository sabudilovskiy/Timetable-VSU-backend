#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>
#include <userver/formats/parse/to.hpp>
namespace userver::formats::parse
{
boost::uuids::uuid Parse(const std::string& value,
                         userver::formats::parse::To<boost::uuids::uuid>);
}
