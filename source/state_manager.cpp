#include "state_manager.hpp"

#include <iostream>

State_Manager::State_Manager(std::shared_ptr<b2World> world,
                             std::shared_ptr<Asset_Manager> asset_manager)
{
    m_world                 = world;
    m_asset_manager         = asset_manager;
}

State_Manager::~State_Manager()
{

}

void State_Manager::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    //handle event only for the top most state
    m_all_states[0]->handle_events(event, window);
}

void State_Manager::update(double delta)
{
    //check if active state requested for change
    unsigned int next_state_id = m_all_states[0]->get_next_state_id();

    if(next_state_id == game_state::null_state)
    {
        //no change, update the active state
        m_all_states[0]->update(delta);
    }
    else
    {
        //change in state required
        unsigned int current_state_id = m_all_states[0]->get_state_id();

        //menu state
        if(current_state_id == game_state::menu)
        {
            if(next_state_id == game_state::play)
            {
                clear_states();
                create_state(game_state::play);
            }
            else if(next_state_id == game_state::quit)
            {
                clear_states();
            }
        }

        //play state
        else if(current_state_id == game_state::play)
        {
            if(next_state_id == game_state::pause_state)
            {
                create_state(game_state::pause_state);
            }
            else if(next_state_id == game_state::game_over)
            {
                create_state(game_state::game_over);
            }
            else if(next_state_id == game_state::level_win)
            {
                create_state(game_state::level_win);
            }
        }

        //pause state
        else if(current_state_id == game_state::pause_state)
        {
            if(next_state_id == game_state::play)
            {
                remove_state();
                m_all_states[0]->reset_next_state_id();
            }
            else if(next_state_id == game_state::menu)
            {
                clear_states();
                create_state(game_state::menu);
            }
        }

        //level win state
        else if(current_state_id == game_state::level_win)
        {
            if(next_state_id == game_state::play)
            {
                clear_states();
                create_state(game_state::play);
            }
            else if(next_state_id == game_state::menu)
            {
                clear_states();
                create_state(game_state::menu);
            }
        }

        //game over state
        else if(current_state_id == game_state::game_over)
        {
            if(next_state_id == game_state::play)
            {
                clear_states();
                create_state(game_state::play);
            }
            else if(next_state_id == game_state::menu)
            {
                clear_states();
                create_state(game_state::menu);
            }
        }

        else
            std::cout << "Undefined state requested\n";
    }

}

void State_Manager::render(std::shared_ptr<sf::RenderWindow> window)
{
    //draw all the states in reverse order
    for(unsigned int i = m_all_states.size(); i > 0; --i)
    {
        m_all_states[i-1]->render(window);
    }
}

void State_Manager::create_state(unsigned int id)
{
    if(id == game_state::menu)
    {
        std::unique_ptr<Menu_State> menu_state(new Menu_State(m_asset_manager));
        m_all_states.push_front(std::move(menu_state));
    }
    else if(id == game_state::play)
    {
        std::unique_ptr<Play_State> play_state(new Play_State(m_world, m_asset_manager));
        m_all_states.push_front(std::move(play_state));
    }
    else if(id == game_state::pause_state)
    {
        std::unique_ptr<Pause_State> pause_state(new Pause_State(m_asset_manager));
        m_all_states.push_front(std::move(pause_state));
    }
    else if(id == game_state::game_over)
    {
        std::unique_ptr<Game_Over_State> game_over_state(new Game_Over_State(m_asset_manager));
        m_all_states.push_front(std::move(game_over_state));
    }
    else if(id == game_state::level_win)
    {
        std::unique_ptr<Level_Win_State> level_win_state(new Level_Win_State(m_asset_manager));
        m_all_states.push_front(std::move(level_win_state));
    }
    else
        std::cout << "request to create undefined state";
}

void State_Manager::remove_state()
{
    m_all_states.pop_front();
}

void State_Manager::clear_states()
{
    m_all_states.clear();
}

bool State_Manager::is_empty() const
{
    return m_all_states.empty();
}


