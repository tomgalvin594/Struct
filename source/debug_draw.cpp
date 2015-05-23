#include "debug_draw.hpp"

void Debug_Draw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}

void Debug_Draw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::ConvexShape convex_polygon(vertexCount);
	for(int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 v = vertices[i];
        convex_polygon.setPoint(i, sf::Vector2f(v.x * TO_PXL, v.y * TO_PXL));
    }
    convex_polygon.setOutlineThickness(1.0);
    convex_polygon.setOutlineColor(B2SFColor(color));
    convex_polygon.setFillColor(B2SFColor(color, 50));
    m_window->draw(convex_polygon);
}

void Debug_Draw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{

}

void Debug_Draw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    sf::CircleShape circle(radius * TO_PXL);
    circle.setPosition( (center.x - radius) * TO_PXL, (center.y - radius) * TO_PXL);
    circle.setOutlineThickness(1.0);
    circle.setOutlineColor(B2SFColor(color));
    circle.setFillColor(B2SFColor(color, 50));
    m_window->draw(circle);
}

void Debug_Draw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(p1.x * TO_PXL, p1.y * TO_PXL);
    line[0].color = B2SFColor(color);
    line[1].position = sf::Vector2f(p2.x * TO_PXL, p2.y * TO_PXL);
    line[1].color = B2SFColor(color);
    m_window->draw(line);
}

void Debug_Draw::DrawTransform(const b2Transform& xf)
{

}

sf::Color Debug_Draw::B2SFColor(const b2Color &color, int a)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8)(a));
	return result;
}

void Debug_Draw::set_window(std::shared_ptr<sf::RenderWindow> window)
{
    m_window = window;
}
