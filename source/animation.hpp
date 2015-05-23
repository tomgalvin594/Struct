#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>

#include <SFML/Graphics.hpp>

//Simple 2D sprite-sheet animation
class Animation
{
public:
							Animation();
							Animation(	sf::Sprite      sprite,
										sf::Vector2i    frame_size,
										unsigned int    start_frame,
										unsigned int    frame_count,
										double          animation_time,
										bool            loop);
							~Animation();

    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

    void                    set_position(sf::Vector2f position);
    void                    start();
    void                    stop();

private:
    sf::Sprite              m_sprite;
    sf::Vector2i            m_sprite_size;
    sf::Vector2i            m_frame_size;
    unsigned int            m_start_frame;
    unsigned int            m_frame_count;
    unsigned int            m_current_frame;
    double                  m_time_per_frame;
    double                  m_animation_time;
    double                  m_elapsed_time;
    bool                    m_loop;
    bool                    m_finish;
};

#endif // ANIMATION_HPP
