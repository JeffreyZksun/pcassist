#pragma once

#include <boost/thread.hpp>

#define THREADSAFE_SINGLETON_DECL(CLS)                          \
public:                                                         \
    static CLS* Get();                                          \
private:                                                        \
    static CLS* _Get();


#define THREADSAFE_SINGLETON_IMPL(CLS)                          \
boost::mutex s_mutex_##CLS;                                     \
CLS* CLS::Get()                                                 \
{                                                               \
    static CLS* p_theOneAndOnlyOne;                             \
    if (p_theOneAndOnlyOne == NULL)                             \
    {                                                           \
        boost::lock_guard<boost::mutex> guard(s_mutex_##CLS);   \
        if (p_theOneAndOnlyOne == NULL)                         \
        {                                                       \
            p_theOneAndOnlyOne = _Get();                        \
        }                                                       \
    }                                                           \
    return p_theOneAndOnlyOne;                                  \
}                                                               \
                                                                \
CLS* CLS::_Get()                                                \
{                                                               \
    static CLS s_theOneAndOnlyOne;                              \
    return &s_theOneAndOnlyOne;                                 \
}
