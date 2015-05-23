#include "animation.hpp"

Animation::Animation()
{

}

Animation::Animation(sf::Sprite    sprite,
                     sf::Vector2i  frame_size,
                     unsigned int  start_frame,
                     unsigned int  frame_count,
                     double        animation_time,
                     bool          loop)
{
    m_sprite                = sprite;
    m_frame_size            = frame_size;
    m_start_frame           = start_frame;
    m_frame_count           = frame_count;
    m_animation_time        = animation_time;
    m_loop                  = loop;

    m_sprite_size.x         = m_sprite.getLocalBounds().width;
    m_sprite_size.y         = m_sprite.getLocalBounds().height;
    m_current_frame         = m_start_frame;
    m_time_per_frame        = m_animation_time / (double)m_frame_count;
    m_elapsed_time          = 0.0;
    m_finish                = true;
}

Animation::~Animation()
{

}

void Animation::update(double delta)
{
    if(!m_finish)
    {
        m_elapsed_time += delta;

        //change current frame if required
        if(m_elapsed_time > (m_current_frame * m_time_per_frame))
        {
            ++m_current_frame;

            //frame reaches end
            if(m_current_frame > m_frame_count)
            {
                if(m_loop)
                {
                    m_current_frame = m_start_frame; //reset
                    m_elapsed_time  = 0.0f;
                }
                else
                    m_finish = true; //end animation
            }
        }

        //calculate texture rectangle for current frame
        int x_offset = (m_current_frame - 1) * m_frame_size.x;
        int x = x_offset % m_sprite_size.x;
        int y = (x_offset / m_sprite_size.x) * m_frame_size.y;

        m_sprite.setTextureRect(sf::IntRect(x, y, m_frame_size.x, m_frame_size.y));
    }
}

void Animation::render(std::shared_ptr<sf::RenderWindow> window)
{
    if(!m_finish)
        window->draw(m_sprite);
}

void Animation::set_position(sf::Vector2f position)
{
    m_sprite.setPosition(position);
}

void Animation::start()
{
    m_finish                = false;
    m_current_frame         = m_start_frame;
    m_elapsed_time          = 0.0;
}

void Animation::stop()
{
    m_finish = true;
}
