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
const std::string RestServiceController::SERVICE_VERSION = "1.0.0";

void RestServiceController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&RestServiceController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&RestServiceController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&RestServiceController::handlePost, this, std::placeholders::_1));

    requestHandler = std::unique_ptr<RequestHandler>(new RequestHandler(SERVICE_NAME, SERVICE_VERSION));
}

void RestServiceController::handleGet(http_request message) {
    requestHandler->handle_get_request(message);
}

void RestServiceController::handlePut(http_request message) {
    requestHandler->handle_put_request(message);
}

void RestServiceController::handlePost(http_request message) {
    requestHandler->handle_post_request(message);
}