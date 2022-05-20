#include "main.h"

Node::Node(){

}

Node::~Node(){

}

void Node::update(){

}

void Node::draw(){

}

int Node::get_node_type(){
    return this->type;
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

int Node::get_xpos(){
    return this->xpos; 
}

int Node::get_ypos(){
    return this->ypos;
}