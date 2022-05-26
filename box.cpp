#include "main.h"

Box::Box(int ypos, int xpos, int height, int width, std::string texture, std::string node_name, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, node_name, canvas)
{
    this->collision->set_layer(BOX_LAYER, SKILL_LAYER|PLAYER_LAYER|MONSTER_LAYER|BOX_LAYER);
}

Box::~Box(){
}

void Box::update(){

}

void Box::draw(){
    int x = this->pos.x;
    int y = this->pos.y;
    int w = this->width; 
    int h = this->height;

    attron(COLOR_PAIR(2)); 
    mvwaddch(this->canvas, y, x, ACS_ULCORNER);         /* Top Left */
    mvwaddch(this->canvas, y, x+w, ACS_URCORNER);      /* Top Right */
    mvwaddch(this->canvas, y+h, x, ACS_LLCORNER);      /* Bottom Left */
    mvwaddch(this->canvas, y+h, x + w, ACS_LRCORNER);  /* Bottom Right */
    
    mvwhline(this->canvas, y,x+1, ACS_HLINE, w-1); 
    mvwhline(this->canvas, y+h, x+1, ACS_HLINE, w-1); 
    mvwvline(this->canvas, y+1, x, ACS_VLINE, h-1); 
    mvwvline(this->canvas, y+1, x+w, ACS_VLINE, h-1);
    attroff(COLOR_PAIR(2));
}

void Box::occur_collision(Actor* subject){

}