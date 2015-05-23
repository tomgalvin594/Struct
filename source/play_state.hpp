#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <vector>
#include <string>
#include <fstream>

#include <SFML/Audio.hpp>

#include <Box2D/Box2D.h>

#include "random.hpp"
#include "state.hpp"
#include "button.hpp"
#include "loading_bar.hpp"
#include "animation.hpp"
#include "block.hpp"
#include "query_callback.hpp"

class Play_State : public State
{
public:
                            Play_State(std::shared_ptr<b2World> world,
                                       std::shared_ptr<Asset_Manager> asset_manager);
                            ~Play_State();

    void                    handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window);
    void                    update(double delta);
    void                    render(std::shared_ptr<sf::RenderWindow> window);

    //read data from a file and build the level from that data
    void                    load_level();

    //create an explosion
    void                    explode();
    //destroy the splinters from the world
    void                    cleanup();

private:
    std::shared_ptr<b2World>    m_world         = nullptr;

    //store all the block objects
    std::vector<std::unique_ptr<Block>> m_all_blocks;

    //store all the shadow sprites(to guide the player)
    std::vector<sf::Sprite>     m_shadow_sprites;

    //sound
    sf::SoundBuffer             m_buffer_1;
    sf::SoundBuffer             m_buffer_2;
    sf::Sound                   m_explosion_snd;
    sf::Sound                   m_click_snd;

    //store the created bodies for explosion
    std::vector<b2Body*>        m_splinters;

    std::unique_ptr<Button>     m_pause_button  = nullptr;
    std::unique_ptr<Loading_Bar>    m_time_bar  = nullptr;
    std::unique_ptr<Loading_Bar>    m_comp_bar  = nullptr;
    std::unique_ptr<Animation>  m_explosion     = nullptr;


    sf::RectangleShape          m_top_rect;
    sf::RectangleShape          m_bottom_rect;

    sf::Clock                   m_clock;
    double                      m_elapsed_time  = 0.0;

    double                      m_level_time    = 25.0; //seconds
    double                      m_current_time  = 0.0;

    unsigned int                m_total_blocks  = 0;
    unsigned int                m_current_blocks    = 0;

    b2Body                      *m_ground_body  = nullptr;
    b2Body                      *m_top_body     = nullptr;
    b2Body                      *m_left_body    = nullptr;
    b2Body                      *m_right_body   = nullptr;

    sf::Sprite                  m_ground_spt;

    unsigned int                m_level_index   = 1;

    b2MouseJoint                *m_mouse_joint  = nullptr;

    double                      m_last_explosion    = 0.0;
    unsigned int                m_explosion_count   = 0;

    //true to get player input and start play
    bool                        m_play          = false;

    sf::Music                   m_music;

    //sf::Text fps;
};

#endif // PLAY_STATE_HPP
