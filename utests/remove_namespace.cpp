#include <userver/utest/utest.hpp>
#include "openapi/doc/serialize/base.hpp"

UTEST(RemoveNamespace, Basic){
    std::string test = "some_namespace::some_class";
    ::openapi::RemoveNamespaces(test);
    EXPECT_EQ(test, "some_namespace.some_class");
}