#include <string>
#include <string_view>
#include <userver/formats/parse/to.hpp>

namespace userver::formats::parse
{
inline std::string Parse(std::string_view item,
                         userver::formats::parse::To<std::string>)
{
    return std::string{item};
}
}  // namespace userver::formats::parse
