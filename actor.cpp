#include "main.h"

Velocity::Velocity(int y, int x){
    this->x = x; 
    this->y = y;
}

Actor::Actor(int ypos, int xpos, chtype texture){
    this->set_position(ypos, xpos);
    this->texture = texture; 
    this->jump_height = 0;
    this->is_floor = false;
    this->is_jump = false;
}

Actor::~Actor(){

}

void Actor::update(){

}

void Actor::draw(){

}

//https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection -
//Collision Box도 이동
void Actor::actor_move(Velocity* velocity){
    this->xpos += velocity->x; 
    this->ypos += velocity->y; 

}


chtype Actor::get_texture(){
    return this->texture;
}