
#include "request_handler.h"

RequestHandler::RequestHandler(const std::string service_name, const std::string service_version) {
    RequestHandler::service_name = service_name;
    RequestHandler::service_version = service_version;
}

void RequestHandler::handle_get_request(http_request &message) {
    auto path = request_path(message);
    if (!path.empty()) {
        if (path.size() == 2 && path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["response"] = json::value::string("test!");
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::NotFound, response_path_not_found());
        }
    } else {
        message.reply(status_codes::OK, response_service_info());
    }
}

void RequestHandler::handle_post_request(http_request &message) {
    auto path = request_path(message);
    if (!path.empty()) {
        if (path.size() == 2 && path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["response"] = json::value::string("test!");
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::NotFound, response_path_not_found());
        }
    } else {
        message.reply(status_codes::OK, response_service_info());
    }
}

void RequestHandler::handle_put_request(http_request &message) {
    message.reply(status_codes::NotImplemented, response_not_impl(methods::PUT));
}

std::vector<utility::string_t> RequestHandler::request_path(const http_request & message) {
    auto relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}

json::value RequestHandler::response_not_impl(const http::method & method) {
    auto response = json::value::object();
    response["http_method"] = json::value::string(method);
    response["response"] = json::value::string("Not Implemented");
    return response ;
}

json::value RequestHandler::response_path_not_found() {
    auto response = json::value::object();
    response["response"] = json::value::string("Path Not Found");
    return response ;
}

json::value RequestHandler::response_service_info() {
    auto response = json::value::object();
    response["service_name"] = json::value::string(service_name);
    response["version"] = json::value::string(service_version);
    response["status"] = json::value::string("ready!");
    return response;
}