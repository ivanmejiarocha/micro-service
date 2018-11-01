//
//  Created by Ivan Mejia on 12/24/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <std_micro_service.hpp>
#include "rest_service_controller.hpp"

using namespace web;
using namespace http;

const std::string RestServiceController::SERVICE_NAME = "Rest Service C++";

void RestServiceController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&RestServiceController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&RestServiceController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&RestServiceController::handlePost, this, std::placeholders::_1));
}

void RestServiceController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path.size() == 2 && path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["service_name"] = json::value::string(SERVICE_NAME);
            response["version"] = json::value::string("0.1.1");
            response["response"] = json::value::string("test!");
            message.reply(status_codes::OK, response);
        } else {
            message.reply(status_codes::NotFound, pathNotFound());
        }
    } else {
        auto response = json::value::object();
        response["service_name"] = json::value::string(SERVICE_NAME);
        response["version"] = json::value::string("0.1.1");
        response["status"] = json::value::string("ready!");
        message.reply(status_codes::OK, response);
    }
}

void RestServiceController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void RestServiceController::handlePost(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

json::value RestServiceController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["service_name"] = json::value::string(SERVICE_NAME);
    response["http_method"] = json::value::string(method);
    response["response"] = json::value::string("Not Implemented");
    return response ;
}

json::value RestServiceController::pathNotFound() {
    auto response = json::value::object();
    response["service_name"] = json::value::string(SERVICE_NAME);
    response["response"] = json::value::string("Path Not Found");
    return response ;
}