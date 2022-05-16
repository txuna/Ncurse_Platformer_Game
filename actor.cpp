#include "main.h"

Actor::Actor(int ypos, int xpos, chtype texture){
    this->ypos = ypos; 
    this->xpos = xpos;
    this->prev_ypos = ypos;
    this->prev_xpos = xpos; 
    this->texture = texture; 
    this->jump_height = 0;
}

Actor::~Actor(){

}

void Actor::update(){

}

void Actor::draw(){

}

// 이전 좌표를 저장한다. 
void Actor::backup_pos(){
    this->prev_xpos = this->xpos; 
    this->prev_ypos = this->ypos; 
}

//이쪽에서 충돌 체크를 진행 할까
void Actor::actor_move(int ypos, int xpos){
    this->ypos = ypos; 
    this->xpos = xpos;
    this->prev_xpos = xpos; 
    this->prev_ypos = ypos;
}

int Actor::get_xpos(){
    return this->xpos; 
}

int Actor::get_ypos(){
    return this->ypos;
}

int Actor::get_prev_xpos(){
    return this->prev_xpos; 
}

int Actor::get_prev_ypos(){
    return this->prev_ypos;
}

chtype Actor::get_texture(){
    return this->texture;
}