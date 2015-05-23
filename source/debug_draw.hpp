#ifndef DEBUG_DRAW_HPP
#define DEBUG_DRAW_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include "globals.hpp"

//b2 debug draw implementation

class Debug_Draw : public b2Draw
{
public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);

	void set_window(std::shared_ptr<sf::RenderWindow> window);

private:
	sf::Color B2SFColor(const b2Color &color, int a = 255);

    std::shared_ptr<sf::RenderWindow> m_window = nullptr;
};

#endif // DEBUG_DRAW_HPP
