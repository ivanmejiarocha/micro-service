//
//  Created by Ivan Mejia on 12/24/16.
//  Copyright © 2016 ivmeroLabs. All rights reserved.
//
//  The software code, programs, and documentation are the confidential and
//  proprietary information of ivmeroLabs Corporation ("Confidential Information").
//  You shall not disclose such Confidential Information and shall use it only
//  in accordance with the terms of the license agreement you entered into
//  with ivmeroLabs or one of its licensed distributors.
//
//  ivmeroLabs MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
//  SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
//  PURPOSE, OR NON-INFRINGEMENT. ivmeroLabs SHALL NOT BE LIABLE FOR ANY DAMAGES
//  SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
//  THIS SOFTWARE OR ITS DERIVATIVES.
//
//

#include <iostream>

#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>

#include "microsvc_controller.hpp"

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[]) {
    InterruptHandler::hookSIGINT();

    MicroserviceController server;
    server.setEndpoint("http://host_auto_ip4:6502/v1/aude/api");
    
    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "Copyright © ivmeroLabs 2016. C++ Microservice now listening for requests at: " << server.endpoint() << '\n';
        
        InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "somehitng wrong happen! :(" << '\n';
    }
    catch(...) {
        RuntimeUtils::printStackTrace();
    }

    return 0;
}
