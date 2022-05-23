#include "main.h"

Label::Label(std::string name, int ypos, int xpos, int height, int width, WINDOW* canvas){
    this->name = name;
    this->canvas = canvas;
    this->set_size(height, width);
    this->set_position(ypos, xpos);
    this->set_visible(true);
    this->prev_xpos = xpos; 
    this->prev_ypos = ypos;
}

Label::~Label(){

}

void Label::update(){

}


void Label::draw(){
    std::string stuff(this->name.length(), ' ');
    int px = this->prev_xpos; 
    int py = this->prev_ypos; 
    int x = this->xpos; 
    int y = this->ypos; 
    WINDOW* win = this->canvas;
    mvwprintw(win, py, px, stuff.c_str());
    mvwprintw(win, y, x, this->name.c_str());
}

void Label::set_name(std::string name){
    this->name = name;
}