#include "game_over_state.hpp"

Game_Over_State::Game_Over_State(std::shared_ptr<Asset_Manager> asset_manager)
{
    m_state_id              = game_state::game_over;
    m_asset_manager         = asset_manager;

    sf::Sprite              button_sprite(m_asset_manager->get_texture("button"));
    sf::Font                slash_font(m_asset_manager->get_font("slash"));

    m_game_over.setFont(m_asset_manager->get_font("slash"));
    m_game_over.setString("TIMES UP");
    m_game_over.setPosition(430, 200);
    m_game_over.setCharacterSize(40);

    std::unique_ptr<Button> t_replay_button(new Button( sf::Vector2f(412, 300),
                                                        sf::Vector2f(1, 1),
                                                        button_sprite,
                                                        slash_font,
                                                        40,
                                                        "REPLAY"));
    m_replay_button = std::move(t_replay_button);

    std::unique_ptr<Button> t_menu_button(new Button(   sf::Vector2f(412,400),
                                                        sf::Vector2f(1, 1),
                                                        button_sprite,
                                                        slash_font,
                                                        40,
                                                        "MENU"));
    m_menu_button = std::move(t_menu_button);
}

Game_Over_State::~Game_Over_State()
{

}

void Game_Over_State::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    m_replay_button->handle_events(event, window);
    m_menu_button->handle_events(event, window);
}

void Game_Over_State::update(double delta)
{
    m_replay_button->update(delta);
    m_menu_button->update(delta);

    if(m_replay_button->get_state() == button_state::button_down)
    {
        m_next_state_id = game_state::play;
    }
    if(m_menu_button->get_state() == button_state::button_down)
    {
        m_next_state_id = game_state::menu;
    }
}

void Game_Over_State::render(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(m_game_over);
    m_replay_button->render(window);
    m_menu_button->render(window);
}

