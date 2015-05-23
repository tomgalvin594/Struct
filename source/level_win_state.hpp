#ifndef LEVEL_WIN_STATE
#define LEVEL_WIN_STATE

#include "state.hpp"
#include "button.hpp"

class Level_Win_State : public State
{
public:
                            Level_Win_State(std::shared_ptr<Asset_Manager> asset_manager);
                            ~Level_Win_State();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

private:
    std::unique_ptr<Button> m_next_button = nullptr;
    std::unique_ptr<Button> m_menu_button = nullptr;
};

#endif // LEVEL_WIN_STATE
