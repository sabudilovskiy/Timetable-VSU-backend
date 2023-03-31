#include "../src/views/hello/view.hpp"
#include <vector>
#include <userver/utest/utest.hpp>


UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(service_template::SayHelloTo("Developer", service_template::UserType::kKnown), "Hi again, Developer!\n");
  EXPECT_EQ(service_template::SayHelloTo("", service_template::UserType::kFirstTime), "Hello, unknown user!\n");
  EXPECT_EQ(service_template::SayHelloTo("Developer", service_template::UserType::kFirstTime), "Hello, Developer!\n");
}
