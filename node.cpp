#include "main.h"

extern int NODE_INDEX;

Node::Node(){
    this->visibility = true;
    this->id = NODE_INDEX;
    NODE_INDEX+=1;
}

Node::~Node(){

}

void Node::update(){

}

void Node::draw(){

}


void Node::set_visible(bool flag){
    this->visibility = flag;
}

bool Node::get_visible(){
    return this->visibility;
}

void Node::set_position(int ypos, int xpos){
    this->ypos = ypos; 
    this->xpos = xpos;
}

void Node::set_size(int height, int width){
    this->height = height; 
    this->width = width;
}

int Node::get_xpos(){
    return this->xpos; 
}

int Node::get_ypos(){
    return this->ypos;
}

int Node::get_width(){
    return this->width;
}

int Node::get_height(){
    return this->height;
}

WINDOW* Node::get_win(){
    return this->win;
}

int Node::get_node_type(){
    return this->type;
}

void Node::transform_position(Velocity* velocity){
    this->prev_xpos = this->xpos; 
    this->prev_ypos = this->ypos;
    this->xpos += velocity->x;
    this->ypos += velocity->y; 
}

int Node::get_id(){
    return this->id;
}

void Node::rollback_pos(){
    this->xpos = this->prev_xpos; 
    this->ypos = this->prev_ypos;
}