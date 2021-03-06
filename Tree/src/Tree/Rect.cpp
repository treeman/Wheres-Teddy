#include "Rect.hpp"

using Tree::Rect;

Rect::Rect( Tree::Vec2f pos, float width, float height, bool is_centered )
{
    Set( pos.x, pos.y, width, height, is_centered );
}
Rect::Rect( float x, float y, float width, float height, bool is_centered )
{
    Set( x, y, width, height, is_centered );
}

void Rect::SetSquare( Tree::Vec2f pos, float size, bool is_centered )
{
    Set( pos.x, pos.y, size, size, is_centered );
}
void Rect::SetSquare( float x, float y, float size, bool is_centered )
{
    Set( x, y, size, size, is_centered );
}
void Rect::Set( float x, float y, float width, float height, bool is_centered )
{
    if( !is_centered ) {
        x1 = x; y1 = y;
        x2 = x + width;
        y2 = y + height;
    }
    else {
        x1 = x - width / 2;
        y1 = y - height / 2;
        x2 = x + width / 2;
        y2 = y + width / 2;
    }
}
void Rect::SetAnchors( float _x1, float _y1, float _x2, float _y2 )
{
    x1 = _x1; y1 = _y1;
    x2 = _x2; y2 = _y2;
}

bool Rect::IsOver( const Tree::Vec2f &pos ) const
{
    return IsOver( pos.x, pos.y );
}
bool Rect::IsOver( float x, float y ) const
{
    return  x > x1 && x < x2 &&
            y > y1 && y < y2;
}

bool Rect::Intersects( const Rect &rect ) const
{
    const float min_x = std::max( x1, rect.x1 );
    const float min_y = std::max( y1, rect.y1 );
    const float max_x = std::min( x2, rect.x2 );
    const float max_y = std::min( y2, rect.y2 );

    return min_x < max_x && min_y < max_y;
}

Tree::Vec2f Rect::GetCenter() const
{
    return Vec2f( x1 + ( x2 - x1 ) / 2, y1 + ( y2 - y1 ) / 2 );
}
