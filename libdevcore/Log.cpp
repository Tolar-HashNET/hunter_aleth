// Aleth: Ethereum C++ client, tools and libraries.
// Copyright 2013-2019 Aleth Authors.
// Licensed under the GNU General Public License, Version 3.
#include "Log.h"

#ifdef __APPLE__
#include <pthread.h>
#endif

namespace dev
{

namespace
{
std::atomic<bool> g_vmTraceEnabled{false};
}  // namespace

std::string getThreadName()
{
#if defined(__GLIBC__) || defined(__APPLE__)
    char buffer[128];
    pthread_getname_np(pthread_self(), buffer, 127);
    buffer[127] = 0;
    return buffer;
#else
    return g_logThreadName.m_name.get() ? *g_logThreadName.m_name.get() : "<unknown>";
#endif
}

void setThreadName(std::string const& _n)
{
#if defined(__GLIBC__)
    pthread_setname_np(pthread_self(), _n.c_str());
#elif defined(__APPLE__)
    pthread_setname_np(_n.c_str());
#else
    g_logThreadName.m_name.reset(new std::string(_n));
#endif
}

void setupLogging(LoggingOptions const& _options)
{
    g_vmTraceEnabled = _options.vmTrace;
}

bool isVmTraceEnabled()
{
    return g_vmTraceEnabled;
}

}  // namespace dev
