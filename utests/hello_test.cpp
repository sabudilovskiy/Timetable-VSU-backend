#include "../src/views/hello/view.hpp"
#include <vector>
#include <userver/utest/utest.hpp>


struct A{
  int a;
  int b;
}; 

struct Any{
  template<class U> operator U(){}
};


UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(service_template::SayHelloTo("Developer", service_template::UserType::kKnown), "Hi again, unknown user!\n");
  EXPECT_EQ(service_template::SayHelloTo("", service_template::UserType::kKnown), "Hi again, unknown user\n");
  std::vector<int> adsd;

}
