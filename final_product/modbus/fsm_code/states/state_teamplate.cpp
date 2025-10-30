
#include "state.hpp"



state::state(callback_ptr handler)
{
    transition_handler = handler;
}

state::~state()
{

}

int state::enter()
{

}

int state::exit()
{
    
}

int state::update()
{
    
}