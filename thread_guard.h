#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#pragma once

#include<vector>
#include<thread>

class thread_gaurd
{
    std::thread &t;

public:
    explicit thread_gaurd(std::thread &_t) : t(_t){}

    ~thread_gaurd()
    {
        if(t.joinable())
        {
            t.join();
        }
    }

    thread_gaurd(const thread_gaurd&) = delete;
    thread_gaurd &operator= (const thread_gaurd&) = delete;

};


#endif // THREAD_GUARD_H
