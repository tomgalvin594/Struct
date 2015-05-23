#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <deque>
#include <memory>

#include <Box2D/Box2D.h>

#include "asset_manager.hpp"
#include "menu_state.hpp"
#include "play_state.hpp"
#include "pause_state.hpp"
#include "level_win_state.hpp"
#include "game_over_state.hpp"

//stores and manages different 'State' objects
class State_Manager
{
public:
                            State_Manager(std::shared_ptr<b2World> world,
                                          std::shared_ptr<Asset_Manager> asset_manager);
                            ~State_Manager();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

    //create a new state
    void                    create_state(unsigned int id);

    //remove the active state
    void                    remove_state();

    //clear the container
    void                    clear_states();

    //if no more states left
    bool                    is_empty() const;

private:
    std::shared_ptr<b2World>                    m_world         = nullptr;
    std::shared_ptr<Asset_Manager>              m_asset_manager = nullptr;

    //store all the states
    std::deque<std::unique_ptr<State>>          m_all_states;
};

#endif // STATE_MANAGER_HPP
