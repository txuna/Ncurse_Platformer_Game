#include "main.h"

Velocity::Velocity(int y, int x){
    this->x = x; 
    this->y = y;
}

Actor::Actor(int ypos, int xpos, int height, int width, std::string texture, std::string node_name, WINDOW* canvas){
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
    this->prev_pos.x = xpos; 
    this->prev_pos.y = ypos;
    this->set_node_name(node_name);
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
    this->prev_pos.x = this->pos.x; 
    this->prev_pos.y = this->pos.y;

    this->pos.x += velocity->x;
    this->pos.y += velocity->y; 
    
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
// is_pass가 아니라면 이전위치로 이동?
void Actor::occur_collision(Actor* subject){

}

/*
 r1은 충돌하는 객체 
 r2는 충돌당하는 객체  
*/

int Actor::get_collision_side(Actor* subject){
    int bit = 0;
    int BoxLeft = this->collision->get_xpos();
    int BoxRight = BoxLeft + this->collision->get_width();
    int BoxTop = this->collision->get_ypos();
    int BoxBottom = BoxTop+this->collision->get_height();

    int oldBoxLeft = this->collision->get_prev_xpos(); 
    int oldBoxRight = oldBoxLeft + this->collision->get_width(); 
    int oldBoxTop = this->collision->get_prev_ypos(); 
    int oldBoxBottom = oldBoxTop + this->collision->get_height();

    int subLeft = subject->collision->get_xpos(); 
    int subRight = subLeft + subject->collision->get_width();
    int subTop = subject->collision->get_ypos(); 
    int subBottom = subTop + subject->collision->get_height();

    /* left or right 충돌 */
    //  subject의 오른쪽과 충돌하면서 this의 right가 subject의 left보다 커짐
    if(oldBoxRight <= subLeft && BoxRight > subLeft){
        bit = bit | LR_SIDE; 
    }
    else if(oldBoxLeft >= subRight && BoxLeft < subRight){
        bit = bit | LR_SIDE; 
    }

    /* bottom or top 충돌 */
    else if(oldBoxBottom <= subTop && BoxBottom > subTop){
        bit = bit | BT_SIDE; 
    }
    else if(oldBoxTop >= subBottom && BoxTop < subBottom){
        bit = bit | BT_SIDE;
    }
    
    return bit; 
}
