#pragma once
#include <boost/uuid/uuid.hpp>

namespace models
{
struct AuthToken
{
    boost::uuids::uuid id;
};
}  // namespace models
