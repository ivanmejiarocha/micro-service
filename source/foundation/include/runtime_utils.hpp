//
//  Created by Ivan Mejia on 12/08/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs. All rights reserved.
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

#pragma once

#include <execinfo.h>
#include <unistd.h>

namespace cfx {
    class RuntimeUtils {
    public:
        static void printStackTrace() {
            const int MAX_CALLSTACK = 100;
            void * callstack[MAX_CALLSTACK];
            int frames;
                        
            // get void*'s for all entries on the stack...
            frames = backtrace(callstack, MAX_CALLSTACK);

            // print out all the frames to stderr...
            backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
        }
    };
}