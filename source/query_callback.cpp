#include "query_callback.hpp"

Query_Callback::Query_Callback(b2Vec2 mouse_position)
{
    m_mouse_position = mouse_position;
}

Query_Callback::~Query_Callback()
{

}

bool Query_Callback::ReportFixture(b2Fixture *fixture)
{
    bool touching = fixture->TestPoint(m_mouse_position);

    if(touching)
    {
        m_body = fixture->GetBody();
        return false;
    }

    return true;
}
