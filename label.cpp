#include "main.h"

Label::Label(std::string name, int ypos, int xpos, int height, int width, WINDOW* canvas){
    this->name = name;
    this->canvas = canvas;
    this->set_size(height, width);
    this->set_position(ypos, xpos);
    this->set_visible(true);
    this->prev_pos.x = xpos; 
    this->prev_pos.y = ypos; 
    this->set_node_name("Label");
}

Label::~Label(){

}

void Label::update(){

}


void Label::draw(){
    std::string stuff(this->name.length(), ' ');
    int px = this->prev_pos.x; 
    int py = this->prev_pos.y; 
    int x = this->pos.x; 
    int y = this->pos.y;
    WINDOW* win = this->canvas;
    mvwprintw(win, py, px, stuff.c_str());
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, y, x, this->name.c_str());
    wattroff(win, COLOR_PAIR(2));
}

void Label::set_name(std::string name){
    this->name = name;
}