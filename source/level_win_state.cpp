#include "level_win_state.hpp"

Level_Win_State::Level_Win_State(std::shared_ptr<Asset_Manager> asset_manager)
{
    m_state_id              = game_state::level_win;
    m_asset_manager         = asset_manager;

    sf::Sprite              button_sprite(m_asset_manager->get_texture("button"));
    sf::Font                slash_font(m_asset_manager->get_font("slash"));

    std::unique_ptr<Button> t_next_button(new Button(   sf::Vector2f(412, 200),
                                                        sf::Vector2f(1, 1),
                                                        button_sprite,
                                                        slash_font,
                                                        40,
                                                        "NEXT"));
    m_next_button = std::move(t_next_button);

    std::unique_ptr<Button> t_menu_button(new Button(   sf::Vector2f(412, 300),
                                                        sf::Vector2f(1, 1),
                                                        button_sprite,
                                                        slash_font,
                                                        40,
                                                        "MENU"));
    m_menu_button = std::move(t_menu_button);
}

Level_Win_State::~Level_Win_State()
{

}

void Level_Win_State::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    m_next_button->handle_events(event, window);
    m_menu_button->handle_events(event, window);
}

void Level_Win_State::update(double delta)
{
    m_next_button->update(delta);
    m_menu_button->update(delta);

    if(m_next_button->get_state() == button_state::button_down)
        m_next_state_id = game_state::play;

    if(m_menu_button->get_state() == button_state::button_down)
        m_next_state_id = game_state::menu;
}

void Level_Win_State::render(std::shared_ptr<sf::RenderWindow> window)
{
    m_next_button->render(window);
    m_menu_button->render(window);
}


