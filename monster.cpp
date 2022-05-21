#include "main.h"

Monster::Monster(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, canvas)
{
    this->velocity = new Velocity(0, 0);
    this->type = T_NON_WIN;
    this->direction = 1;
}

Monster::~Monster(){
    delete velocity;
}

void Monster::update(){
    //LEFT
    this->velocity->x = SPEED * direction;
    if(this->xpos + velocity->x + this->width >= WIDTH
    || this->xpos + velocity->x <= 0){
        velocity->x = 0; 
        direction = direction * -1;
    }
        //중력 적용
        if(this->ypos + this->velocity->y + this->height < HEIGHT-2){
            this->velocity->y = GRAVITY;
        }else{
            this->velocity->y = 0;
        }
    this->actor_move(this->velocity);
}

void Monster::draw(){
    std::string stuff(this->width, ' ');
    mvwaddstr(this->canvas, this->prev_ypos, this->prev_xpos, stuff.c_str());
    mvwaddstr(this->canvas,  this->ypos, this->xpos, this->texture.c_str());
    mvprintw(3, 3, "(%d:%d)", this->ypos, this->xpos);
    refresh();
}