/**************************************************************************
 *
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

// File: vogl_common.h
#ifndef VOGL_COMMON_H
#define VOGL_COMMON_H

#define _MULTI_THREADED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <dlfcn.h>

#include <pthread.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xmd.h>

#include "gl_types.h"

#include "vogl_core.h"
#include "vogl_threading.h"

#include "libtelemetry.h"

using namespace vogl;

#define VOGL_API_EXPORT extern "C" __attribute__((visibility("default")))

// DO NOT leave this enabled when you check in!
#ifndef VOGL_FUNCTION_TRACING
#define VOGL_FUNCTION_TRACING 0
#endif

#if VOGL_FUNCTION_TRACING
extern bool g_vogl_enable_function_tracing;

class vogl_scoped_func_tracer
{
    const char *m_pFunc;
    uint m_line;

public:
    vogl_scoped_func_tracer(const char *pFunc, uint line)
    {
        m_pFunc = NULL;
        if (!g_vogl_enable_function_tracing)
            return;
        m_pFunc = pFunc;
        m_line = line;
        printf("IN %s %u\n", pFunc, line);
    }

    ~vogl_scoped_func_tracer()
    {
        if (!g_vogl_enable_function_tracing)
            return;
        if (m_pFunc)
            printf("OUT %s %u\n", m_pFunc, m_line);
    }
};

#define VOGL_FUNC_TRACER                                                                          \
    vogl_scoped_func_tracer VOGL_JOIN(func_tracer, __COUNTER__)(__PRETTY_FUNCTION__, __LINE__); \
    tmZone(TELEMETRY_LEVEL1, TMZF_NONE, "%s", __PRETTY_FUNCTION__);
#else
#define VOGL_FUNC_TRACER tmZone(TELEMETRY_LEVEL1, TMZF_NONE, "%s", __PRETTY_FUNCTION__);
#endif

#define VOGL_NAMESPACES_HEADER
#include "vogl_namespaces.h"
#undef VOGL_NAMESPACES_HEADER

#include "vogl_ctypes.h"
#include "vogl_entrypoints.h"
#include "vogl_gl_utils.h"

void vogl_common_lib_early_init();
void vogl_common_lib_global_init();

#endif // VOGL_COMMON_H
