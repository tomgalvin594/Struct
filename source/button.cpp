#include "button.hpp"

#include <iostream>

Button::Button( sf::Vector2f position,
                sf::Vector2f scale,
                sf::Sprite sprite,
                sf::Font font,
                unsigned int char_size,
                std::string label)
{
    m_position              = position;
    m_sprite                = sprite;
    m_font                  = font;

    m_sprite = sprite;
    m_sprite.setPosition(position);
    m_sprite.setScale(scale);

    m_text.setFont(m_font);
    m_text.setString(label);
    m_text.setCharacterSize(char_size);

    float sprite_w = m_sprite.getGlobalBounds().width;
    float sprite_h = m_sprite.getGlobalBounds().height;

    float label_w = m_text.getGlobalBounds().width;
    float label_h = m_text.getGlobalBounds().height;

    float y_offset = (m_font.getLineSpacing(char_size) - m_text.getCharacterSize()) * 1.5f;

    m_text.setOrigin(label_w / 2, label_h / 2);
    m_text.setPosition(position.x + sprite_w/2, position.y + sprite_h/2 - y_offset);
}

Button::~Button()
{

}

void Button::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    if(event.type == sf::Event::MouseMoved)
    {
        int x = window->mapPixelToCoords({event.mouseMove.x,0}).x;
        int y = window->mapPixelToCoords({0,event.mouseMove.y}).y;
        if(is_mouse_over_button(x, y))
            m_state = button_state::button_select;
        else
            m_state = button_state::button_general;
    }
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(m_state == button_state::button_select)
            m_state = button_down;
    }
}

void Button::update(float delta)
{
    if(m_state == button_state::button_general)
        m_sprite.setColor(sf::Color(200, 200, 200, 255));

    else if(m_state == button_state::button_select)
        m_sprite.setColor(sf::Color(255, 255, 255, 255));

    else if(m_state == button_state::button_down)
        m_sprite.setColor(sf::Color(255, 255, 255, 255));
}

void Button::render(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(m_sprite);
    window->draw(m_text);
}

void Button::set_scale(sf::Vector2f scale)
{
    m_sprite.setScale(scale);
}

void Button::set_character_size(unsigned int size)
{
    m_text.setCharacterSize(size);
}

void Button::reset_state()
{
    m_state = button_state::button_general;
}

unsigned int Button::get_state() const
{
    return m_state;
}

bool Button::is_mouse_over_button(int mouse_x, int mouse_y)
{
    float top_left_x        = m_position.x;
    float top_left_y        = m_position.y;
    float top_right_x       = m_position.x + m_sprite.getGlobalBounds().width;
    float bottom_left_y     = m_position.y + m_sprite.getGlobalBounds().height;

    if( mouse_x >= top_left_x &&
        mouse_x <= top_right_x &&
        mouse_y >= top_left_y &&
        mouse_y <= bottom_left_y)
            return true;

    return false;
}
