#include "loading_bar.hpp"

Loading_Bar::Loading_Bar(   sf::Vector2f position,
                            sf::Vector2f size,
                            sf::Color back_color,
                            sf::Color front_color)
{
    m_position              = position;
    m_size                  = size;
    m_back_color            = back_color;
    m_front_color           = front_color;

    m_back_rect.setPosition(position);
    m_back_rect.setSize(size);
    m_back_rect.setFillColor(back_color);

    m_front_rect.setPosition(position);
    m_front_rect.setFillColor(front_color);
}

Loading_Bar::~Loading_Bar()
{

}

void Loading_Bar::update(double fill_ratio)
{
    if(fill_ratio >= 0.0 && fill_ratio <= 1.0) //clip
    {
        double progress = m_size.x * fill_ratio;
        m_front_rect.setSize(sf::Vector2f(progress, m_size.y));
    }
}

void Loading_Bar::render(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(m_back_rect);
    window->draw(m_front_rect);
}
