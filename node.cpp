#include "main.h"

Node::Node(){
    this->visibility = true;
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


WINDOW* Node::get_win(){
    return this->win;
}

int Node::get_node_type(){
    return this->type;
}