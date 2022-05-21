#include "main.h"

Monster::Monster(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, canvas)
{
    this->velocity = new Velocity(0, 0);
    this->direction = 1;
    this->collision->set_layer(MONSTER_LAYER, PLAYER_LAYER);
}

Monster::~Monster(){
    delete this->velocity;

}

void Monster::update(){
    //LEFT
    this->velocity->x = SPEED * this->direction;
    if(this->xpos + velocity->x + this->width >= WIDTH
    || this->xpos + velocity->x <= 0){
        velocity->x = 0; 
        this->direction = this->direction * -1;
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
    mvprintw(4, 1, "Monster : (%d:%d)", this->ypos, this->xpos);
    mvprintw(5, 1, "Collision : (%d:%d)", this->collision->get_ypos(), this->collision->get_xpos());
    refresh();
}