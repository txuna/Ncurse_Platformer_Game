#include "main.h"

Fireball::Fireball(int direction, int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, "Fireball", canvas)
{
    this->velocity = new Velocity(0, 0); 
    this->collision->set_layer(SKILL_LAYER, MONSTER_LAYER|BOX_LAYER);  
    this->direction = direction;
    this->distance = 8;
}

Fireball::~Fireball(){
    delete this->velocity;
}

void Fireball::update(){
    refresh();
    this->velocity->x = SPEED * this->direction; 
    this->actor_move(this->velocity);
    this->distance += 1;
}

void Fireball::draw(){
     std::string stuff(this->width, ' ');
     mvwaddstr(this->canvas, this->prev_pos.y, this->prev_pos.x, stuff.c_str());
     mvwaddstr(this->canvas,  this->pos.y, this->pos.x, this->texture.c_str());
}

void Fireball::occur_collision(Actor* subject){

}