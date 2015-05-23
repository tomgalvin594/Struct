#include "play_state.hpp"

#include "resource_path.hpp"

Play_State::Play_State(std::shared_ptr<b2World> world,
                       std::shared_ptr<Asset_Manager> asset_manager)
{
    m_state_id              = game_state::play;

    m_world                 = world;
    m_asset_manager         = asset_manager;

    sf::Sprite              button_sprite(m_asset_manager->get_texture("button"));
    sf::Font                slash_font(m_asset_manager->get_font("slash"));

    //pause button
    std::unique_ptr<Button> t_pause_button(new Button(  sf::Vector2f(10, 60),
                                           sf::Vector2f(1, 1),
                                           button_sprite,
                                           slash_font,
                                           40,
                                           "PAUSE"));
    m_pause_button = std::move(t_pause_button);

    //bars
    std::unique_ptr<Loading_Bar> t_time_bar(new Loading_Bar(sf::Vector2f(20, 30),
                                            sf::Vector2f(980, 1),
                                            sf::Color(50, 50, 50),
                                            sf::Color::Red));
    m_time_bar = std::move(t_time_bar);

    std::unique_ptr<Loading_Bar> t_comp_bar(new Loading_Bar(sf::Vector2f(20, 50),
                                            sf::Vector2f(980, 1),
                                            sf::Color(50, 50, 50),
                                            sf::Color(0, 128, 255)));
    m_comp_bar = std::move(t_comp_bar);

    m_music.openFromFile(resourcePath() + "asset//music//music.ogg");
    m_music.setLoop(true);
    m_music.setVolume(30);

    //sound
    m_buffer_1.loadFromFile(resourcePath() + "asset//music//explosion.wav");
    m_explosion_snd.setBuffer(m_buffer_1);

    m_buffer_2.loadFromFile(resourcePath() + "asset//music//click.wav");
    m_click_snd.setBuffer(m_buffer_2);

    //explosion animation
    sf::Sprite explosion_spt(m_asset_manager->get_texture("explosion"));
    explosion_spt.setScale(2.5, 2.5);
    std::unique_ptr<Animation> t_explosion(new Animation(   explosion_spt,
                                           sf::Vector2i(64, 64),
                                           1,
                                           16,
                                           1.0,
                                           false));
    m_explosion = std::move(t_explosion);

    //rectangles
    m_top_rect.setPosition(-50, -50);
    m_top_rect.setSize(sf::Vector2f(1200, 200));
    m_top_rect.setFillColor(sf::Color::Black);

    m_bottom_rect.setPosition(-50, 650);
    m_bottom_rect.setSize(sf::Vector2f(1200, 200));
    m_bottom_rect.setFillColor(sf::Color::Black);

    //the ground
    b2BodyDef ground_bd;
    ground_bd.position.Set(0, 785.0 * TO_MTR);
    m_ground_body = world->CreateBody(&ground_bd);
    b2PolygonShape ground_ps;
    ground_ps.SetAsBox(1200.0 * TO_MTR, 70.0 * TO_MTR);
    m_ground_body->CreateFixture(&ground_ps, 0.0);

    //top
    b2BodyDef top_bd;
    top_bd.position.Set(0, 0);
    m_top_body = world->CreateBody(&top_bd);
    b2PolygonShape top_ps;
    top_ps.SetAsBox(1200.0 * TO_MTR, 70.0 * TO_MTR);
    m_top_body->CreateFixture(&top_ps, 0.0);

    //left
    b2BodyDef left_bd;
    left_bd.position.Set(0, 0);
    m_left_body = world->CreateBody(&left_bd);
    b2PolygonShape left_ps;
    left_ps.SetAsBox(10.0 * TO_MTR, 1200.0 * TO_MTR);
    m_left_body->CreateFixture(&left_ps, 0.0);

    //right
    b2BodyDef right_bd;
    right_bd.position.Set(1020.0 * TO_MTR, 0.0);
    m_right_body = world->CreateBody(&right_bd);
    b2PolygonShape right_ps;
    right_ps.SetAsBox(10.0 * TO_MTR, 1200 * TO_MTR);
    m_right_body->CreateFixture(&right_ps, 0.0);

    //sprites
    m_ground_spt.setTexture(m_asset_manager->get_texture("ground"));
    m_ground_spt.setScale(1.0, 0.2);
    m_ground_spt.setPosition(0, 715);

    //fps.setPosition(50, 90);
    //fps.setFont(asset_manager->get_font("slash"));

    load_level();
}

Play_State::~Play_State()
{
    if(m_ground_body)
    {
        m_world->DestroyBody(m_ground_body);
        m_ground_body = nullptr;
    }
    if(m_top_body)
    {
        m_world->DestroyBody(m_top_body);
        m_top_body = nullptr;
    }
    if(m_left_body)
    {
        m_world->DestroyBody(m_left_body);
        m_left_body = nullptr;
    }
    if(m_right_body)
    {
        m_world->DestroyBody(m_right_body);
        m_right_body = nullptr;
    }
}

void Play_State::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    if(m_play)
    {
        m_pause_button->handle_events(event, window);

        auto iter_1 = m_all_blocks.begin();
        while(iter_1 != m_all_blocks.end())
        {
            (*iter_1)->handle_events(event, window);
            ++iter_1;
        }

        //mouse move
        if(event.type == sf::Event::MouseMoved)
        {
            float m_x = window->mapPixelToCoords({event.mouseMove.x,0}).x;
            float m_y = window->mapPixelToCoords({0,event.mouseMove.y}).y;

            if(m_mouse_joint)
                m_mouse_joint->SetTarget(b2Vec2(m_x * TO_MTR, m_y * TO_MTR));
        }

        //mouse click
        if(event.type == sf::Event::MouseButtonPressed)
        {
            float m_x = window->mapPixelToCoords({event.mouseButton.x,0}).x;
            float m_y = window->mapPixelToCoords({0,event.mouseButton.y}).y;

            //query for mouse over game objects
            b2AABB aabb;
            aabb.upperBound.Set(m_x * TO_MTR + 1, m_y * TO_MTR + 1);
            aabb.lowerBound.Set(m_x * TO_MTR - 1, m_y * TO_MTR - 1);
            Query_Callback query_callback(b2Vec2(m_x * TO_MTR, m_y * TO_MTR));
            m_world->QueryAABB(&query_callback, aabb);
            b2Body *body = query_callback.m_body;
            if(body)
            {
                if(body->GetType() == b2_dynamicBody)
                {
                    b2MouseJointDef md;
                    md.bodyA = m_ground_body;
                    md.bodyB = body;
                    md.target = b2Vec2(m_x * TO_MTR, m_y * TO_MTR);
                    md.maxForce = 1000.0f * body->GetMass();
                    m_mouse_joint = (b2MouseJoint*)m_world->CreateJoint(&md);
                    body->SetAwake(true);
                    body->SetFixedRotation(true);
                }
            }
        }

        //mouse release
        if(event.type == sf::Event::MouseButtonReleased)
        {
            if(m_mouse_joint)
            {
                m_click_snd.play();
                m_world->DestroyJoint(m_mouse_joint);
                m_mouse_joint = nullptr;
            }
        }

        //key press
        if(event.type == sf::Event::KeyPressed)
        {

        }
    }
}

void Play_State::update(double delta)
{
    //std::string fps_str = convert<std::string, int>(1.0f / delta);
    //fps.setString(fps_str);

    m_elapsed_time = m_clock.getElapsedTime().asSeconds();

    //play not started, show the explosions
    if(!m_play)
    {
        if(m_explosion_count < 4) //number of explosions
        {
            if(m_last_explosion > 1.0) //gap between two explosions
            {
                ++m_explosion_count;
                cleanup();
                m_explosion_snd.play();
                explode();
                m_explosion->start();
                m_last_explosion = 0.0; //reset time
            }
            else
                m_last_explosion += delta;
        }
        else
        {
            //start play
            m_play = true;
            //m_music.play();
            cleanup();
        }
    }
    else
    {
        m_current_time += delta;

        //game over
    if(m_current_time >= m_level_time)
    {
        m_next_state_id = game_state::game_over;
    }

    //player win
    if(m_current_blocks == m_total_blocks)
    {
        ++m_level_index;
        if(m_level_index > 10) //no of levels
            m_level_index = 1;
        std::fstream reader(resourcePath() + "level//level_data");
        reader << m_level_index;
        reader.close();
        m_next_state_id = game_state::level_win;
    }

        m_top_rect.move(0, -120.0 * delta);
        m_bottom_rect.move(0, 120.0 * delta);

        if(m_pause_button->get_state() == button_state::button_down)
        {
            m_next_state_id = game_state::pause_state;
            m_pause_button->reset_state();
        }
    }

    //update UI elements
    m_pause_button->update(delta);
    m_time_bar->update(m_current_time / m_level_time);
    m_comp_bar->update((double)m_current_blocks / (double)m_total_blocks);

    m_explosion->update(delta);

    //update physics
    m_world->Step(1.0f / 60.0f, 8, 3);
    m_world->ClearForces();

    m_current_blocks = 0;
    auto iter = m_all_blocks.begin();
    while(iter != m_all_blocks.end())
    {
        (*iter)->update(delta);

        if((*iter)->in_start_position())
        {
            ++m_current_blocks;
        }

        ++iter;
    }
    if(!m_play)
        m_current_blocks = 0;
}

void Play_State::render(std::shared_ptr<sf::RenderWindow> window)
{
    //shadow sprites
    auto iter_1 = m_shadow_sprites.begin();
    while(iter_1 != m_shadow_sprites.end())
    {
        window->draw(*iter_1);
        ++iter_1;
    }

    window->draw(m_ground_spt);

    //blocks
    auto iter_2 = m_all_blocks.begin();
    while(iter_2 != m_all_blocks.end())
    {
        (*iter_2)->render(window);
        ++iter_2;
    }

    m_pause_button->render(window);
    m_time_bar->render(window);
    m_comp_bar->render(window);

    m_explosion->render(window);

    //rectangles
    window->draw(m_top_rect);
    window->draw(m_bottom_rect);

    //window->draw(fps);
}

void Play_State::load_level()
{
    //reset old data
    m_all_blocks.clear();
    m_shadow_sprites.clear();
    m_clock.restart();
    m_elapsed_time          = 0;
    m_current_time          = 0;
    m_current_blocks        = 0;
    m_last_explosion        = 0;
    m_explosion_count       = 0;
    m_play                  = false;
    m_top_rect.setPosition(-50, -50);
    m_bottom_rect.setPosition(-50, 650);

    //the ground
    b2BodyDef ground_bd;
    ground_bd.position.Set(0, 785.0 * TO_MTR);

    std::fstream reader(resourcePath() + "level//level_data");
    reader >> m_level_index;
    reader.close();

    std::array<double, 10> time_table{12, 18, 23, 25, 30, 32, 35, 37, 40, 42};
    m_level_time = time_table[m_level_index-1];

    std::string level_path = resourcePath() + "level//level_" + convert<std::string, int>(m_level_index);
    reader.open(level_path);
    std::vector<float> level_data;
    while(1)
    {
        float value;
        reader >> value;
        level_data.push_back(value);

        if(reader.eof())
            break;
    }
    reader.close();

    const unsigned int PACKET_SIZE = 6;
    for(unsigned int i = 0; i < level_data.size(); i += PACKET_SIZE)
    {
        unsigned int id     = (int)level_data[i];
        float p_x           = level_data[i+1];
        float p_y           = level_data [i+2] + 214.0;
        float s_x           = level_data[i+3];
        float s_y           = level_data[i+4];
        float angle         = level_data[i+5];

        sf::Sprite sprite;
        sprite.setPosition(p_x, p_y);
        sprite.setScale(s_x, s_y);
        sprite.setRotation(angle);

        if(id >= 1 && id <= 19)
        {
            std::string txr_id = "block_" + convert<std::string, int>(id);
            sprite.setTexture(m_asset_manager->get_texture(txr_id));
            unsigned int body_shape = shape::rectangle;
            if(id >= 13 && id <= 16)
                body_shape = shape::circle;
            if(id == 17 || id == 18)
                body_shape = shape::triangle;

            std::unique_ptr<Block> t_block(new Block(m_world, m_asset_manager, sprite,
                                           body_shape, type::dynamic_body));
            m_all_blocks.push_back(std::move(t_block));
        }

        sprite.setColor(sf::Color(100, 100, 100, 200));
        m_shadow_sprites.push_back(sprite);
    }

    m_total_blocks = m_all_blocks.size();
}

void Play_State::explode()
{
    Random rng;

    b2Vec2 position;
    position.x = rng.random(50.0, 950.0) * TO_MTR;
    position.y = rng.random(500.0, 600.0) * TO_MTR;

    m_explosion->set_position(sf::Vector2f(position.x * TO_PXL, position.y * TO_PXL));

    for(int i = 0; i < 20; ++i)
    {
        float   angle       = ((float)i / 20.0) * 360.0f * TO_RAD;
        b2Vec2  direction(sinf(angle), cosf(angle));

        b2BodyDef body_def;
        body_def.type           = b2_dynamicBody;
        body_def.fixedRotation  = true;
        body_def.bullet         = true;
        body_def.linearDamping  = 5.0;
        body_def.gravityScale   = 0.0;
        body_def.position       = position;
        body_def.linearVelocity = 200.0 * direction;
        b2Body *body = m_world->CreateBody(&body_def);

        b2CircleShape circle_shape;
        circle_shape.m_p.Set(0.1, 0.1);
        circle_shape.m_radius   = 0.1;

        b2FixtureDef fixture_def;
        fixture_def.shape       = &circle_shape;
        fixture_def.density     = 25.0f;
        fixture_def.friction    = 0.0;
        fixture_def.restitution = 1.0;
        body->CreateFixture(&fixture_def);

        m_splinters.push_back(body);
    }
}

void Play_State::cleanup()
{
    for(unsigned int i = 0; i < m_splinters.size(); ++i)
    {
        if(m_splinters[i])
        {
            m_world->DestroyBody(m_splinters[i]);
            m_splinters[i] = nullptr;
        }
    }
}
