#include "fsm.hpp"

state current_state;

state state_list[sizeof(NUM_STATES)] = 
{
    state(transition)
}; 

int setup_fsm()
{
    idle_state idle;
    state_list[IDLE] = idle;

    
    current_state = idle;
    return 0;
}

int execute_fsm ()
{
    current_state.update();
    return 0;
}

void* transition (state_enum older, state_enum newer)
{
    if (older != newer)
        return 0;

    if (newer % NUM_STATES)
        return 0;

    current_state.exit();
    current_state = state_list[newer];
    current_state.enter();

    return 0;
}