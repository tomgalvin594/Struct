#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "globals.hpp"
#include "asset_manager.hpp"

//represents a basic building block of the game city
class Block
{
public:
                            Block();
                            Block(std::shared_ptr<b2World> world,
                                  std::shared_ptr<Asset_Manager> asset_manager,
                                  sf::Sprite &sprite,
                                  unsigned int body_shape,
                                  unsigned int body_type);
                            ~Block();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window); //!!!
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

    void                    set_physics(float density, float friction, float restitution);

    //if block is in staring position
    bool                    in_start_position() const;

    //if mouse is over its starting position
    bool                    mouse_over_rect(float mouse_x, float mouse_y);

private:
    std::shared_ptr<b2World>                    m_world         = nullptr;
    std::shared_ptr<Asset_Manager>              m_asset_manager = nullptr;

    sf::Sprite              m_sprite;

    //starting position of the block
    sf::Vector2f            m_start_position;

    sf::Clock               m_clock;
    double                  m_elapsed_time      = 0.0;

    //if picked by player
    bool                    m_picked            = false;

    //if block is in its starting position
    bool                    m_in_start_position = true;

    b2Body                  *m_body             = nullptr;
};

#endif // BLOCK_HPP
