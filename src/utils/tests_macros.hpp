#pragma once

#include <gtest/gtest.h>

#include <string>

#define EXPECT_THROW_MSG(statement, type_exception, message) \
    do                                                       \
    {                                                        \
        bool _throwed_unknown_exception = false;             \
        bool _throwed_exception = false;                     \
        std::string _got_msg;                                \
        std::string _expected_msg(message);                  \
        try                                                  \
        {                                                    \
            statement;                                       \
        }                                                    \
        catch (const type_exception& exc)                    \
        {                                                    \
            _got_msg = exc.what();                           \
            _throwed_exception = true;                       \
        }                                                    \
        catch (...)                                          \
        {                                                    \
            _throwed_unknown_exception = true;               \
        }                                                    \
        EXPECT_FALSE(_throwed_unknown_exception);            \
        EXPECT_TRUE(_throwed_exception);                     \
        EXPECT_EQ(_got_msg, _expected_msg);                  \
    } while (false)

namespace impl
{
inline std::string drop_first_and_last_symbol(std::string_view text)
{
    return std::string{text.substr(1, text.size() - 2)};
}
}  // namespace impl

#define RAW_STRING(X) impl::drop_first_and_last_symbol(X)
