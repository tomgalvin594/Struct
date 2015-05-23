#include <iostream>
#include <memory>
#include <string>
#include <cassert>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

#include "debug_draw.hpp"
#include "asset_manager.hpp"
#include "state_manager.hpp"

int main()
{
    //SFML window
    const unsigned int WND_W = 1024;
    const unsigned int WND_H = 768;

    std::shared_ptr<sf::RenderWindow> window(new sf::RenderWindow
                    (sf::VideoMode(WND_W, WND_H), "Struct", sf::Style::Default)); //sf::Style::Fullscreen));

    //b2 world
    std::shared_ptr<b2World> world(new b2World(b2Vec2(0.0, 9.8)));

    //debug draw
    Debug_Draw debug_draw;
    debug_draw.set_window(window);
    debug_draw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
    world->SetDebugDraw(&debug_draw);

    //asset manager
    std::shared_ptr<Asset_Manager> asset_manager(new Asset_Manager);
    asset_manager->load();

    //state manager
    std::unique_ptr<State_Manager> state_manger(new State_Manager(world, asset_manager));
    state_manger->create_state(game_state::menu);

    sf::Sprite back_spt(asset_manager->get_texture("back"));

    sf::Clock main_clock;
    double delta = 0.0;

    //sf::Text fps;
    //fps.setPosition(50, 50);
    //fps.setFont(asset_manager->get_font("slash"));

    double value = 0.0;
    const double TIME_STEP = 1.0 / 60.0;
    const double MAX_FRAME_TIME = 0.025;

    while(window->isOpen())
    {
        delta = main_clock.restart().asSeconds();
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window->close();

            state_manger->handle_events(event, window);
        }

        //std::string fps_str = convert<std::string, int>(1.0f / delta);
        //fps.setString(fps_str);

        //if(delta > MAX_FRAME_TIME)
        //    delta = MAX_FRAME_TIME;

        value += delta;
        while(value >= TIME_STEP)
        {
            state_manger->update(TIME_STEP);
            if(state_manger->is_empty())
                window->close();
            value -= TIME_STEP;
        }

        window->clear();
        window->draw(back_spt);
        //world->DrawDebugData();
        state_manger->render(window);
        //window->draw(fps);
        window->display();
    }

    return 0;
}
