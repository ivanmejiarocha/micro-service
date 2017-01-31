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
#include "microsvc_controller.hpp"

#include "user_manager.hpp"

using namespace web;
using namespace http;

void MicroserviceController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&MicroserviceController::handlePatch, this, std::placeholders::_1));
}

void MicroserviceController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["version"] = json::value::string("0.1.1");
            response["status"] = json::value::string("ready!");
            message.reply(status_codes::OK, response);
        }
        else if (path[0] == "users" && path[1] == "signon") {
            pplx::create_task([=]() -> std::tuple<bool, UserInformation> {
                auto headers = message.headers();
                if (message.headers().find("Authorization") == headers.end()) 
                    throw std::exception();
                auto authHeader = headers["Authorization"];
                auto credsPos = authHeader.find("Basic");
                if (credsPos == std::string::npos) 
                    throw std::exception();
                
                auto base64 = authHeader.substr(credsPos + 
                                std::string("Basic").length() + 1);
                if (base64.empty()) 
                    throw std::exception();
                auto bytes = utility::conversions::from_base64(base64);
                std::string creds(bytes.begin(), bytes.end());
                auto colonPos = creds.find(":");
                if (colonPos == std::string::npos) 
                    throw std::exception();
                auto useremail = creds.substr(0, colonPos);
                auto password = creds.substr(colonPos + 1, creds.size()  - colonPos - 1);            
                        
                UserManager users;
                UserInformation userInfo;            
                if (users.signOn(useremail, password, userInfo)) {
                return std::make_tuple(true, userInfo);
                }
                else {
                return std::make_tuple(false, UserInformation {});
                }
            })
            .then([=](pplx::task<std::tuple<bool, UserInformation>> resultTsk) {
                try {
                    auto result = resultTsk.get();
                    if (std::get<0>(result) == true) {
                        json::value response;
                        response["success"] = json::value::string("welcome " + std::get<1>(result).name + "!");                    
                        message.reply(status_codes::OK, response);
                    }
                    else {
                        message.reply(status_codes::Unauthorized);
                    }
                }
                catch(std::exception) {
                    message.reply(status_codes::Unauthorized);
                }
            });
        }
    }
    else {
        message.reply(status_codes::NotFound);
    }
}

void MicroserviceController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void MicroserviceController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void MicroserviceController::handlePost(http_request message) {
    auto path = requestPath(message);
    if (!path.empty() && 
         path[0] == "users" && 
         path[1] == "signup") {
        message.
        extract_json().
        then([=](json::value request) {
            try {
                UserInformation userInfo { 
                    request.at("email").as_string(),
                    request.at("password").as_string(),
                    request.at("name").as_string(),
                    request.at("lastName").as_string()
                };
                UserManager users;
                users.signUp(userInfo);
                json::value response;
                response["message"] = json::value::string(
                                        "succesful registration!");
                message.reply(status_codes::OK, response);
            }
            catch(UserManagerException & e) {
                message.reply(status_codes::BadRequest, e.what());
            }
            catch(json::json_exception & e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }
}

void MicroserviceController::handleDelete(http_request message) {    
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void MicroserviceController::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void MicroserviceController::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void MicroserviceController::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void MicroserviceController::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void MicroserviceController::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value MicroserviceController::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["serviceName"] = json::value::string("C++ Mircroservice Sample");
    response["http_method"] = json::value::string(method);
    return response ;
}