#include "main.h"

extern int NODE_INDEX;
extern GameManager* game_manager; 

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
    pos.y = ypos; 
    pos.x = xpos; 
}

void Node::set_size(int height, int width){
    this->height = height; 
    this->width = width;
}

int Node::get_xpos(){
    return this->pos.x; 
}

int Node::get_ypos(){
    return this->pos.y;
}

int Node::get_prev_xpos(){
    return this->prev_pos.x; 
}

int Node::get_prev_ypos(){
    return this->prev_pos.y; 
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
    this->prev_pos.x = this->pos.x; 
    this->prev_pos.y = this->pos.y;
    this->pos.x += velocity->x; 
    this->pos.y += velocity->y; 
}

int Node::get_id(){
    return this->id;
}

void Node::rollback_pos(){
    this->pos.x = this->prev_pos.x; 
    this->pos.y = this->prev_pos.y;
}

void Node::rollback_xpos(){
    this->pos.x = this->prev_pos.x; 
}

void Node::rollback_ypos(){
    this->pos.y = this->prev_pos.y;
}

void Node::set_node_name(std::string node_name){
    this->node_name = node_name;
}

std::string Node::get_node_name(){
    return this->node_name;
}


void Node::append_node(Node* node){
    this->sub_objects.push_back(node);
}

/*
Node* Node::get_node(std::string node_name){
    for(auto const& obj : this->sub_objects){
        if(node->get_node_name() == node_name){
            return node;
        }
        Node* node = obj->get_node(node_name); 
        if(node == NULL){
            continue;
        }
        
    }
    return NULL;
}
*/