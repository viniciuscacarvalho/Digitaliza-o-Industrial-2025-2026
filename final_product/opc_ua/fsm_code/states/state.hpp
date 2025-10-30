#ifndef __STATE_CLASS__
#define __STATE_CLASS__

#include "state_list.hpp"

typedef void* (*callback_ptr) (state_enum, state_enum);

class state
{
private:
    static callback_ptr transition_handler;
public:
    state();
    state(callback_ptr handler);
    ~state();
    int enter();
    int exit();
    int update();
};



#endif