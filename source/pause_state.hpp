#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "state.hpp"
#include "button.hpp"

class Pause_State : public State
{
public:
                            Pause_State(std::shared_ptr<Asset_Manager> asset_manager);
                            ~Pause_State();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

private:
    std::unique_ptr<Button> m_resume_button = nullptr;
    std::unique_ptr<Button> m_menu_button = nullptr;
};

#endif // PAUSE_STATE_HPP
