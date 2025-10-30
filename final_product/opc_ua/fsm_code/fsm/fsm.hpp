#ifndef __FSM_HEADER__
#define __FSM_HEADER__

#include "../states/state.hpp"
#include "../states/idle_state.hpp"
int setup_fsm();

int execute_fsm();

void* transition (state_enum older, state_enum newer);


#endif