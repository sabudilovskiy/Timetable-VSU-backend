#include "perform_common_errors.hpp"

namespace timetable_vsu_backend::utils::common_errors
{
Response400 PerformLoginTaken()
{
    Response400 resp;
    resp.description = "Account can't created: login is already taken";
    resp.machine_id = "LOGIN_TAKEN";
    return resp;
}
Response401 PerformInvalidToken()
{
    Response401 resp;
    resp.description = "Account not founded: token invalid";
    resp.machine_id = "INVALID_TOKEN";
    return resp;
}
Response403 PerformForbidden()
{
    Response403 resp;
    resp.description = "Not enough permissions to do so";
    resp.machine_id = "NOT_ENOUGH_PERMISSIONS";
    return resp;
}
Response400 PerformInvalidData(std::string_view message)
{
    Response400 resp;
    resp.description = message;
    resp.machine_id = "INVALID_DATA";
    return resp;
}
}  // namespace timetable_vsu_backend::utils::common_errors
