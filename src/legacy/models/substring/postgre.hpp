#pragma once
#include <userver/storages/postgres/io/string_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include "type.hpp"

namespace userver::storages::postgres::io
{
using ::legacy::models::SubString;
template <>
struct CppToSystemPg<SubString> : PredefinedOid<PredefinedOids::kText>
{
};

template <>
struct BufferFormatter<SubString>
{
    using CharFormatter = BufferFormatter<const char*>;
    const SubString& value;

    explicit BufferFormatter(const SubString& val) : value{val}
    {
    }
    template <typename Buffer>
    void operator()(const UserTypes&, Buffer& buf) const
    {
        CharFormatter::WriteN(buf, "%", 1);
        CharFormatter::WriteN(buf, value.data(), value.size());
        CharFormatter::WriteN(buf, "%", 1);
    }
};

template <>
struct BufferParser<SubString>
{
    SubString& value;

    explicit BufferParser(SubString& val) : value{val}
    {
    }

    void operator()(const FieldBuffer& buffer)
    {
        value.GetUnderlying() = buffer.ToString();
    }
};
}  // namespace userver::storages::postgres::io
