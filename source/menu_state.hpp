#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Audio.hpp>

#include "state.hpp"
#include "button.hpp"

class Menu_State : public State
{
public:
                            Menu_State(std::shared_ptr<Asset_Manager> asset_manager);
                            ~Menu_State();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

private:
    std::unique_ptr<Button> m_play_button = nullptr;
    std::unique_ptr<Button> m_exit_button = nullptr;

    sf::Text                    m_name;
    sf::Text                    m_about;

    sf::Music                   m_music;
};

#endif // MENU_STATE_HPP
