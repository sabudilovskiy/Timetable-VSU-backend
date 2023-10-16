#pragma once
#include <boost/uuid/uuid.hpp>

namespace legacy::models
{
struct AuthToken
{
    boost::uuids::uuid id;
};
}  // namespace legacy::models
