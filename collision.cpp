#include "main.h"

// Collision Class 
Collision::Collision(int ypos, int xpos, int height, int width){
    this->set_size(height, width);
    this->set_position(ypos, xpos);
    this->set_visible(false);
    this->is_collision = true;
    this->is_pass = false;
    this->type = T_NON_WIN;
}

Collision::~Collision(){

}

void Collision::enable_collision(bool flag){
    this->is_collision = flag;
}

void Collision::set_layer(char layer, char mask){
    this->layer = this->layer | layer;
    this->mask = this->mask | mask;
}

char Collision::get_layer(){
    return this->layer; 
}

char Collision::get_mask(){
    return this->mask;
}

bool Collision::check_mask(char victim_layer){
    if(this->mask & victim_layer){
        return true; 
    }else{
        return false;
    }
}

void Collision::update(){

}

void Collision::draw(){
    
}
