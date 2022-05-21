#include "main.h"

Velocity::Velocity(int y, int x){
    this->x = x; 
    this->y = y;
}

Actor::Actor(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas){
    this->set_position(ypos, xpos);
    this->set_size(height, width);
    this->texture = texture; 
    this->jump_height = 0;
    this->is_floor = false;
    this->is_jump = false;
    this->canvas = canvas;
    this->type = ACTOR;
    this->collision = new Collision(ypos, xpos, height, width);
    this->sub_objects.push_back((Node*)this->collision);
}

Actor::~Actor(){
    for(auto const& obj : this->sub_objects){
        delete obj;
    }
}

void Actor::update(){

}

void Actor::draw(){

}

//https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection -
//Collision Box도 이동
void Actor::actor_move(Velocity* velocity){
    this->prev_xpos = this->xpos; 
    this->prev_ypos = this->ypos;

    this->xpos += velocity->x;
    this->ypos += velocity->y; 
    
    // 상위객체가 이동하면 하위객체도 같은 거리만큼 이동
    for(auto const& obj : this->sub_objects){
        obj->transform_position(velocity);
    }
}

std::string Actor::get_texture(){
    return this->texture;
}

void Actor::set_canvas_win(WINDOW* canvas){
    if(canvas == NULL){
        return; 
    }
    this->canvas = canvas;
}

// 충돌시 어떤 객체와 충돌했는지
void Actor::occur_collision(Actor* subject){
    mvprintw(1, 30, "COLLISION! %d", subject->get_id());
    refresh();
}