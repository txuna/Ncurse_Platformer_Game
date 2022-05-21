#include "main.h"

Velocity::Velocity(int y, int x){
    this->x = x; 
    this->y = y;
}

Actor::Actor(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas){
    this->set_position(ypos, xpos);
    this->set_size(height, width);
    this->texture = texture; 
    this->jump_height = 0;
    this->is_floor = false;
    this->is_jump = false;
    this->canvas = canvas;
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
    this->prev_xpos = this->xpos; 
    this->prev_ypos = this->ypos;
    this->xpos += velocity->x; 
    this->ypos += velocity->y; 

}

std::string Actor::get_texture(){
    return this->texture;
}
