#include "menu_state.hpp"

#include "resource_path.hpp"

Menu_State::Menu_State(std::shared_ptr<Asset_Manager> asset_manager)
{
    m_state_id              = game_state::menu;
    m_asset_manager         = asset_manager;

    sf::Sprite              button_sprite(m_asset_manager->get_texture("button"));
    sf::Font                slash_font(m_asset_manager->get_font("slash"));

    std::unique_ptr<Button> t_play_button(new Button(sf::Vector2f(412, 370),
                                                     sf::Vector2f(1, 1),
                                                     button_sprite,
                                                     slash_font,
                                                     40,
                                                     "PLAY"));
    m_play_button = std::move(t_play_button);

    std::unique_ptr<Button> t_exit_button(new Button(sf::Vector2f(412, 470),
                                                     sf::Vector2f(1, 1),
                                                     button_sprite,
                                                     slash_font,
                                                     40,
                                                     "EXIT"));
    m_exit_button = std::move(t_exit_button);

    m_music.openFromFile(resourcePath() + "asset//music//music.ogg");
    m_music.setLoop(true);
    m_music.setVolume(60);
    m_music.play();

    //name
    m_name.setFont(m_asset_manager->get_font("slash"));
    m_name.setString("STRUCT");
    m_name.setPosition(350, 100);
    m_name.setCharacterSize(100);

    //about
    m_about.setFont(m_asset_manager->get_font("slash"));
    m_about.setString("BY PRITOM BORDOLOI");
    m_about.setPosition(422, 220);
    m_about.setCharacterSize(20);
}

Menu_State::~Menu_State()
{

}

void Menu_State::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    m_play_button->handle_events(event, window);
    m_exit_button->handle_events(event, window);
}

void Menu_State::update(double delta)
{
    m_play_button->update(delta);
    m_exit_button->update(delta);

    //clicked on play
    if(m_play_button->get_state() == button_state::button_down)
        m_next_state_id = game_state::play;

    //clicked on exit
    if(m_exit_button->get_state() == button_state::button_down)
        m_next_state_id = game_state::quit;
}

void Menu_State::render(std::shared_ptr<sf::RenderWindow> window)
{
    m_play_button->render(window);
    m_exit_button->render(window);

    window->draw(m_name);
    window->draw(m_about);
}
