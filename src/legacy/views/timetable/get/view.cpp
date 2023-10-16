#include "view.hpp"

#include <chrono>
#include <exception>
#include <userver/components/component_context.hpp>
#include <userver/components/component_list.hpp>
#include <userver/formats/parse/boost_uuid.hpp>
#include <userver/formats/parse/to.hpp>
#include <userver/formats/serialize/boost_uuid.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/logging/log.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/datetime.hpp>
#include <utils/convert/http_request_parse.hpp>
#include <utils/convert/http_response_serialize.hpp>
#include <utils/convert/json_parse.hpp>
#include <utils/convert/json_serialize.hpp>

#include "Request.hpp"
#include "Responses.hpp"
#include "legacy/components/controllers/postgres/lesson/controller.hpp"
#include "http/handler_parsed.hpp"
#include "legacy/models/day/all.hpp"
#include "legacy/models/education_type/all.hpp"
#include "legacy/models/lesson_v1/parse.hpp"
#include "legacy/models/lesson_v1/serialize.hpp"
#include "legacy/models/user_type/type.hpp"

static_assert(userver::formats::common::impl::kHasSerialize<
              userver::formats::json::Value, ::legacy::models::LessonType>);
namespace legacy::views::timetable::get
{
namespace
{
namespace pg = legacy::components::controllers::postgres;
class Handler final : public http::HandlerParsed<Request, Response200>
{
   public:
    static constexpr std::string_view kName = "handler-timetable-get";
    Handler(const userver::components::ComponentConfig& config,
            const userver::components::ComponentContext& context)
        : HandlerParsed(config, context),
          lesson_controller(context.FindComponent<pg::lesson::Controller>())
    {
    }
    static void ValidateBeginEnd(Request& request)
    {
        if (request.filter() and request.filter()->begin() and
            request.filter()->end() &&
            request.filter()->begin().value() > request.filter()->end().value())
        {
            std::swap(request.filter()->begin().value(),
                      request.filter()->end().value());
        }
    }
    Response Handle(Request&& request) const override
    {
        Response200 resp;
        ValidateBeginEnd(request);
        resp.lessons() = lesson_controller.Search(request.filter());
        return resp;
    }

   private:
    const pg::lesson::Controller& lesson_controller;
};
}  // namespace

void Append(userver::components::ComponentList& component_list)
{
    component_list.Append<Handler>();
}

}  // namespace legacy::views::timetable::get
