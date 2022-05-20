#include "main.h"

// Collision Class 
Collision::Collision(int ypos, int xpos){
    this->set_position(ypos, xpos);
    this->set_visible(false);
}

Collision::~Collision(){

}

void Collision::enable_collision(bool flag){
    this->is_collision = flag;
}

void Collision::update(){

}

void Collision::draw(){
    
}
