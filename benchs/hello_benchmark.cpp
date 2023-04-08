#include <benchmark/benchmark.h>

#include <cstdint>   // for std::uint64_t
#include <iterator>  // for std::size
#include <string_view>
#include <userver/engine/run_standalone.hpp>

#include "views/hello/view.hpp"

void HelloBenchmark(benchmark::State& state) {
    userver::engine::RunStandalone([&] {
        constexpr std::string_view kNames[] = {"userver", "is", "awesome", "!"};
        std::uint64_t i = 0;

        for (auto _ : state) {
            const auto name = kNames[i++ % std::size(kNames)];
            auto result = service_template::SayHelloTo(
                name, service_template::UserType::kKnown);
            benchmark::DoNotOptimize(result);
        }
    });
}

BENCHMARK(HelloBenchmark);
