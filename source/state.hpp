#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "globals.hpp"
#include "asset_manager.hpp"

//abstract class representing a game state
class State
{
public:
                            State();
    virtual                 ~State();

    virtual void            handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window) = 0;
    virtual void            update(double delta) = 0;
    virtual void            render(std::shared_ptr<sf::RenderWindow> window) = 0;

    unsigned int            get_state_id() const;
    unsigned int            get_next_state_id() const;
    void                    reset_next_state_id();

protected:
    std::shared_ptr<Asset_Manager>  m_asset_manager = nullptr;

    unsigned int            m_state_id = game_state::null_state;

    //when a state is done, next state is created from this value
    unsigned int            m_next_state_id = game_state::null_state;
};

#endif // STATE_HPP
