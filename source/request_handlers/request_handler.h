#ifndef MICRO_SERVICE_POST_REQUEST_HANDLER_H
#define MICRO_SERVICE_POST_REQUEST_HANDLER_H
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class RequestHandler {

public:

    RequestHandler(const std::string service_name, const std::string service_version);

    void handle_get_request(http_request& message);
    void handle_post_request(http_request& message);
    void handle_put_request(http_request& message);

protected:
    std::vector<utility::string_t> request_path(const http_request & message);

private:

    std::string service_name;
    std::string service_version;

    json::value response_service_info();
    json::value response_not_impl(const http::method & method);
    json::value response_path_not_found();
};


#endif //MICRO_SERVICE_POST_REQUEST_HANDLER_H
