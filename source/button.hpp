#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "globals.hpp"

//represents a button for GUI

class Button
{
public:
                            Button(sf::Vector2f position,
                                   sf::Vector2f scale,
                                   sf::Sprite sprite,
                                   sf::Font font,
                                   unsigned int char_size,
                                   std::string label);

                            ~Button();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(float delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

    //button configuration
    void                    set_scale(sf::Vector2f scale);
    void                    set_character_size(unsigned int size);
    void                    reset_state();

    //get current state of the button
    unsigned int            get_state() const;

private:
    //is mouse cursor is over button
    bool                    is_mouse_over_button(int mouse_x, int mouse_y);

    sf::Vector2f            m_position;
    sf::Sprite              m_sprite;
    sf::Font                m_font;
    sf::Text                m_text;

    //current state of the button
    unsigned int            m_state = button_state::button_general;
};

#endif // BUTTON_HPP
