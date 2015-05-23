#include "state.hpp"

State::State()
{

}

State::~State()
{

}

unsigned int State::get_state_id() const
{
    return m_state_id;
}

unsigned int State::get_next_state_id() const
{
    return m_next_state_id;
}

void State::reset_next_state_id()
{
    m_next_state_id = game_state::null_state;
}
