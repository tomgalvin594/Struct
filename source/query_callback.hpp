#ifndef QUERY_CALLBACK_HPP
#define QUERY_CALLBACK_HPP

#include <Box2D/Box2D.h>

class Query_Callback : public b2QueryCallback
{
public:
                            Query_Callback(b2Vec2 mouse_position);
                            ~Query_Callback();

    bool                    ReportFixture(b2Fixture *fixture);

    b2Vec2                  m_mouse_position;
    b2Body                  *m_body = nullptr;
};

#endif // QUERY_CALLBACK_HPP
