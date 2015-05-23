#include "block.hpp"

Block::Block()
{

}

Block::Block(   std::shared_ptr<b2World> world,
                std::shared_ptr<Asset_Manager> asset_manager,
                sf::Sprite &sprite,
                unsigned int body_shape,
                unsigned int body_type)
{
    m_world                 = world;
    m_asset_manager         = asset_manager;
    m_sprite                = sprite;

    //get all the required data from the given sprite
    float x         = m_sprite.getPosition().x * TO_MTR;
    float y         = m_sprite.getPosition().y * TO_MTR;
    float w         = m_sprite.getLocalBounds().width * TO_MTR;
    float h         = m_sprite.getLocalBounds().height * TO_MTR;
    float angle     = m_sprite.getRotation() * TO_RAD;
    float s_x       = m_sprite.getScale().x;
    float s_y       = m_sprite.getScale().y;

    m_start_position.x = x * TO_PXL;
    m_start_position.y = y * TO_PXL;

    //calculate dimensions of the physics body
    //divide by 2 because b2 creates boxes twice the given size
    float width     = w * s_x / 2;
    float height    = h * s_y / 2;

    //body definition
    b2BodyDef body_def;

    if(body_type == type::static_body)
    {
        body_def.type = b2_staticBody;
    }
    if(body_type == type::kinematic_body)
    {
        body_def.type = b2_kinematicBody;
    }
    if(body_type == type::dynamic_body)
    {
        body_def.type = b2_dynamicBody;
    }

    body_def.position.Set(x, y);
    body_def.angle = angle;

    m_body = m_world->CreateBody(&body_def);
    m_body->SetGravityScale(0.0);
    m_body->SetAwake(false);

    //fixture definition are different for different shapes
    b2FixtureDef fixture_def;

    if(body_shape == shape::rectangle)
    {
        b2PolygonShape rectangle_shape;
        rectangle_shape.SetAsBox(width, height, b2Vec2(width, height), 0);

        fixture_def.shape   = &rectangle_shape;
        fixture_def.density = 1.0;
        m_body->CreateFixture(&fixture_def);
    }

    if(body_shape == shape::circle)
    {
        b2CircleShape circle_shape;
        circle_shape.m_p.Set(width, height);
        circle_shape.m_radius   = width;

        fixture_def.shape   = &circle_shape;
        fixture_def.density = 1.0;
        fixture_def.friction = 0.5;
        m_body->CreateFixture(&fixture_def);
    }

    if(body_shape == shape::triangle)
    {
        b2Vec2 vertices[3];

        vertices[0].Set(width, 0.0f);
        vertices[1].Set(width * 2.0f, height * 2.0f);
        vertices[2].Set(0.0f, height * 2.0f);

        b2PolygonShape triangle_shape;
        triangle_shape.Set(vertices, 3);

        fixture_def.shape         = &triangle_shape;
        fixture_def.density       = 1.0f;
        m_body->CreateFixture(&fixture_def);
    }
}

Block::~Block()
{
    if(m_world && m_body)
    {
        m_world->DestroyBody(m_body);
        m_body = nullptr;
    }
}

void Block::handle_events(sf::Event &event, std::shared_ptr<sf::RenderWindow> window)
{
    //mouse release
    if(event.type == sf::Event::MouseButtonReleased)
    {
        float m_x = window->mapPixelToCoords({event.mouseButton.x,0}).x;
        float m_y = window->mapPixelToCoords({0,event.mouseButton.y}).y;

        if(m_picked)
        {
            //block is released by player
            if(mouse_over_rect(m_x, m_y))
            {
                m_body->SetTransform(b2Vec2(m_start_position.x * TO_MTR,
                                            m_start_position.y * TO_MTR), 0);
                m_body->SetType(b2_staticBody);
            }
        }
    }
}

void Block::update(double delta)
{
    m_elapsed_time = m_clock.getElapsedTime().asSeconds();

    //transform sprite with b2 body
    m_sprite.setRotation(m_body->GetAngle() * TO_DEG);
    m_sprite.setPosition(m_body->GetPosition().x * TO_PXL, m_body->GetPosition().y * TO_PXL);

    m_in_start_position = false;
    if(m_sprite.getPosition().x == m_start_position.x &&
       m_sprite.getPosition().y == m_start_position.y)
    {
        m_in_start_position = true;
    }

    if(m_in_start_position)
    {
        m_body->SetGravityScale(0.0);
        m_sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    else
    {
        m_body->SetGravityScale(1.0);
        m_sprite.setColor(sf::Color(155, 155, 155, 255));
    }

    m_picked = false;
    if(m_body)
    {
        b2JointEdge *je = m_body->GetJointList();
        if(je)
        {
            //player picked this body
            m_picked = true;
            m_sprite.setColor(sf::Color::Red);
        }
    }
}

void Block::render(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(m_sprite);
}

void Block::set_physics(float density, float friction, float restitution)
{
    b2Fixture *fixture = m_body->GetFixtureList();
    if(fixture)
    {
        fixture->SetDensity(density);
        fixture->SetFriction(friction);
        fixture->SetRestitution(restitution);
    }
}

bool Block::in_start_position() const
{
    return m_in_start_position;
}

bool Block::mouse_over_rect(float mouse_x, float mouse_y)
{
    float top_left_x        = m_start_position.x;
    float top_left_y        = m_start_position.y;
    float top_right_x       = top_left_x + m_sprite.getGlobalBounds().width;
    float bottom_left_y     = top_left_y + m_sprite.getGlobalBounds().height;

    if(     mouse_x >= top_left_x &&
            mouse_x <= top_right_x &&
            mouse_y >= top_left_y &&
            mouse_y <= bottom_left_y)
        return true;

    return false;
}
