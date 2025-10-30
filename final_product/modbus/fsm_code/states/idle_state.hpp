#ifndef __IDLE_STATE_CLASS__
#define __IDLE_STATE_CLASS__

#include "state.hpp"

class idle_state : public state
{
private:
    static callback_ptr transition_handler;
public:
    idle_state();
    idle_state(callback_ptr handler);
    ~idle_state();
    int enter();
    int exit();
    int update();
};

#endif