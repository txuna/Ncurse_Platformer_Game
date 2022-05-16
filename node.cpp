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
