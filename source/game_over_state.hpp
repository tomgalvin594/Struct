#ifndef GAME_OVER_STATE
#define GAME_OVER_STATE

#include "state.hpp"
#include "button.hpp"

class Game_Over_State : public State
{
public:
                            Game_Over_State(std::shared_ptr<Asset_Manager> asset_manager);
                            ~Game_Over_State();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

private:
    std::unique_ptr<Button> m_replay_button = nullptr;
    std::unique_ptr<Button> m_menu_button   = nullptr;

    sf::Text                m_game_over;
};

#endif // GAME_OVER_STATE
