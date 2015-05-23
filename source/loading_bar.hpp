#ifndef LOADING_BAR_HPP
#define LOADING_BAR_HPP

#include <memory>

#include <SFML/Graphics.hpp>

class Loading_Bar
{
public:
                            Loading_Bar(sf::Vector2f position,
                                        sf::Vector2f size,
                                        sf::Color back_color,
                                        sf::Color front_color);
                            ~Loading_Bar();

    void                    update(double fill_ratio);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

private:
    sf::Vector2f            m_position;
    sf::Vector2f            m_size;
    sf::Color               m_back_color;
    sf::Color               m_front_color;
    //current items / total items
    double                  m_fill_ratio;

    sf::RectangleShape      m_back_rect;
    sf::RectangleShape      m_front_rect;
};

#endif // LOADING_BAR_HPP
