#include "Tree/Tweaks.hpp"
#include "MovingObject.hpp"

using Tree::Vec2f;

MovingObject::MovingObject() :
    size( (int)Tree::GetTweaks()->GetDouble( "tile_size" ) )
{
    SetFaceDown();
}

void MovingObject::MoveLeft()
{
    if( WantsRight() ) {
        vel.x = -GetSpeed(); vel.y = 0;
        stop_pos.Set( stop_pos.x - size, pos.y );
        FaceLeft();
    }
    else if( !IsMoving() ) {
        vel.x = -GetSpeed(); vel.y = 0;
        stop_pos.Set( pos.x - size, pos.y );
        FaceLeft();
    }
    else {
        next_move = Vec2f::left;
    }
}
void MovingObject::MoveRight()
{
    if( WantsLeft() ) {
        vel.x = GetSpeed(); vel.y = 0;
        stop_pos.Set( stop_pos.x +  size, pos.y );
        FaceLeft();
    }
    else if( !IsMoving() ) {
        vel.x = GetSpeed(); vel.y = 0;
        stop_pos.Set( pos.x + size, pos.y );
        FaceRight();
    }
    else {
        next_move = Vec2f::right;
    }
}
void MovingObject::MoveUp()
{
    if( !IsMoving() || vel.x != 0 ) {
        vel.x = 0; vel.y = -GetSpeed();
        stop_pos.Set( pos.x, pos.y - size );
        FaceUp();
    }
    else {
        next_move = Vec2f::up;
    }
}
void MovingObject::MoveDown()
{
    if( !IsMoving() || vel.x != 0 ) {
        vel.x = 0; vel.y = GetSpeed();
        stop_pos.Set( pos.x, pos.y + size );
        FaceDown();
    }
    else {
        next_move = Vec2f::down;
    }
}

void MovingObject::Stop()
{
    next_move = Vec2f::zero;
}

bool MovingObject::IsMoving()
{
    return vel.x != 0 || vel.y != 0;
}
bool MovingObject::WantsStop()
{
    return next_move == Vec2f::zero;
}
bool MovingObject::WantsLeft()
{
    return vel.x < 0;
}
bool MovingObject::WantsRight()
{
    return vel.x > 0;
}
bool MovingObject::WantsUp()
{
    return vel.y < 0;
}
bool MovingObject::WantsDown()
{
    return vel.y > 0;
}

bool MovingObject::FacesLeft()
{
    return Vec2f::left == face_dir;
}
bool MovingObject::FacesRight()
{
    return Vec2f::right == face_dir;
}
bool MovingObject::FacesUp()
{
    return Vec2f::up == face_dir;
}
bool MovingObject::FacesDown()
{
    return Vec2f::down == face_dir;
}

void MovingObject::UpdateMovement( float dt )
{
    pos += vel * dt;

    //if we're moving past our stop point, stop there
    if( IsMoving() ) {
        if( WantsLeft() && pos.x < stop_pos.x ) {
            if( next_move == Vec2f::left ) {
                stop_pos.x = stop_pos.x - size;
            }
            else {
                ForceStop();
            }
        }
        else if( WantsRight() && pos.x > stop_pos.x ) {
            if( next_move == Vec2f::right ) {
                stop_pos.x = stop_pos.x + size;
            }
            else {
                ForceStop();
            }
        }
        else if( WantsUp() && pos.y < stop_pos.y ) {
            ForceStop();
        }
        else if( WantsDown() && pos.y > stop_pos.y ) {
            ForceStop();
        }
    }

    //if we have a next move, update our movement dir
    if( !WantsStop() ) {
        if( WantsLeft() ) { MoveLeft(); }
        else if( WantsRight() ) { MoveRight(); }
        else if( WantsUp() ) { MoveUp(); }
        else if( WantsDown() ) { MoveDown(); }
    }
}

void MovingObject::FaceLeft()
{
    SetFaceLeft();
    face_dir = Vec2f::left;
}
void MovingObject::FaceRight()
{
    SetFaceRight();
    face_dir = Vec2f::right;
}
void MovingObject::FaceUp()
{
    SetFaceUp();
    face_dir = Vec2f::up;
}
void MovingObject::FaceDown()
{
    SetFaceDown();
    face_dir = Vec2f::down;
}

void MovingObject::ForceStop()
{
    pos = stop_pos;
    vel = Vec2f::zero;
}
