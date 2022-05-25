#include "main.h"

Monster::Monster(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, canvas)
{
    this->velocity = new Velocity(0, 0);
    this->direction = 1;
    this->collision->set_layer(MONSTER_LAYER, PLAYER_LAYER|BOX_LAYER|MONSTER_LAYER);
    this->label = new Label("Monster", ypos-2, xpos, height, width, canvas);
    this->sub_objects.push_back((Node*)this->label);
}

Monster::~Monster(){
    delete this->velocity;

}

void Monster::update(){
    //LEFT
    this->velocity->x = SPEED * this->direction;
    if(this->pos.x + this->velocity->x + this->width >= WIDTH
    || this->pos.x + this->velocity->x <= 0){
        this->velocity->x = 0; 
        this->direction = this->direction * -1;
    }
    //중력 적용
    if(this->pos.y + this->velocity->y + this->height < HEIGHT-2){
        this->velocity->y = GRAVITY;
    }else{
        this->velocity->y = 0;
    }
    this->actor_move(this->velocity);
}

void Monster::draw(){
    // 하위 객체 렌더링
    for(auto const& obj : this->sub_objects){
        if(!obj->get_visible()){
            continue;
        }
        obj->draw();
    }
    std::string stuff(this->width, ' ');
    mvwaddstr(this->canvas, this->prev_pos.y, this->prev_pos.x, stuff.c_str());
    mvwaddstr(this->canvas,  this->pos.y, this->pos.x, this->texture.c_str());
    mvprintw(4, 1, "Monster : (%d:%d)", this->pos.y, this->pos.x);
    //mvprintw(5, 1, "Collision : (%d:%d)", this->collision->get_ypos(), this->collision->get_xpos());
    refresh();
}

/*
몬스터는 충돌 발생시 기존방향과 반대로 이동
*/
void Monster::occur_collision(Actor* subject){
    int bit = this->get_collision_side(subject);
    // 하위객체도 롤백
    for(auto const& obj : this->sub_objects){
        if(bit & LR_SIDE){
            obj->rollback_xpos();
        }else if(bit & BT_SIDE){
            obj->rollback_ypos();
        }
    }
    if(bit & LR_SIDE){
        this->rollback_xpos(); 
        this->direction = direction * -1;
    }
    else if(bit & BT_SIDE){
        this->rollback_ypos(); 
    }else{
        this->rollback_pos();
    }

    int collision_layer = subject->collision->get_layer(); 
    if(collision_layer == PLAYER_LAYER){
        // 무적상태라면 충돌 체크 X 
        if(((Player*)subject)->get_invincible()) return;
    }
}