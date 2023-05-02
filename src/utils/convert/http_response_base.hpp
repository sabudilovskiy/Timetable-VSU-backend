#pragma once
#include <userver/server/http/http_status.hpp>

#include "utils/meta.hpp"

namespace userver::server::http {
class HttpResponse;
}

namespace timetable_vsu_backend::utils::convert {
struct HttpResponse {
    userver::server::http::HttpResponse& response;
    std::string& body;
    userver::server::http::HttpResponse& operator()() {
        return response;
    }
    userver::server::http::HttpResponse& operator()() const {
        return response;
    }
};
template <typename T>
concept HasStatusCode = requires {
    { T::kStatusCode }
    ->std::convertible_to<userver::server::http::HttpStatus>;
    requires IsConstexpr<T::kStatusCode>;
};
}  // namespace timetable_vsu_backend::utils::convert
