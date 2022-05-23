#include "main.h"

Player::Player(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, canvas)
{
    this->velocity = new Velocity(0, 0);
    this->collision->set_layer(PLAYER_LAYER, MONSTER_LAYER|BOX_LAYER);
    this->is_invincible = false; 
    this->invincible_duration = 0;
    this->label = new Label("tuuna", ypos-2, xpos, height, width, canvas);
    this->sub_objects.push_back((Node*)this->label);
}

Player::~Player(){
    delete this->velocity;
}
//여기에 키 입력?
// 매 프레임마다 업데이트 Godot을 치면 _process 느낌
void Player::update(){
    // 하위 종속 객체 update 
    /*
    for(auto const& obj : this->sub_objects){
        obj->update();
    }
    */
    // 무적 루틴 해제 및 설정 
    if(this->is_invincible){
        if(this->invincible_duration >= INVINCIBLE_TIME){
            this->is_invincible = false; 
            this->invincible_duration = 0;
        }
        else{
            this->invincible_duration += 1;
        }
    }
    //this->velocity->x = 0; 한번의 키로 쭉 진행
    if(kbhit()){
        int ch = getch(); 
        if(ch == KEY_LEFT){
            this->velocity->x = -SPEED; 
        }
        else if(ch == KEY_RIGHT){
            this->velocity->x = SPEED;
        }
        else if(ch == KEY_UP){
            if(!this->is_jump && this->is_floor){
                this->is_jump = true;
            }
        }
        else if(ch == KEY_DOWN){
            this->velocity->x = 0;
        }
    }
    
    if(this->is_jump){
        if(this->jump_height >= JUMP){
            this->is_jump = false; 
            this->jump_height = 0;
            this->is_floor = false;
        }else{
            this->velocity->y = -SPEED; 
            this->jump_height += 1; 
        }
    }else{
        //중력 적용
        if(this->ypos + this->velocity->y + this->height < HEIGHT-2){
            this->velocity->y = GRAVITY;
            this->is_floor = false;
            //this->velocity->y += GRAIVITY; // 원래는 이건데 터미널은 소수점을 표현못해서 ㅎㅎ
        }else{
            this->velocity->y = 0;
            this->is_floor = true;
        }
    }
    // 벽 
    if(this->xpos + this->velocity->x + this->width >= WIDTH
    || this->xpos + this->velocity->x <= 0){
        this->velocity->x = 0; 
    }
    this->actor_move(this->velocity);
}

void Player::draw(){
    // 하위 객체 렌더링
    for(auto const& obj : this->sub_objects){
        if(!obj->get_visible()){
            continue;
        }
        obj->draw();
    }
    std::string stuff(this->width, ' ');
    mvwaddstr(this->canvas, this->prev_ypos, this->prev_xpos, stuff.c_str());
    mvwaddstr(this->canvas,  this->ypos, this->xpos, this->texture.c_str());
    mvprintw(1, 1, "Player : (%d:%d)", this->ypos, this->xpos);
    mvprintw(2, 1, "Collision : (%d:%d)", this->collision->get_ypos(), this->collision->get_xpos());
    refresh();
}


/*
몬스터를 만날시 1.5초간 무적 상태를 설정한다. 
그렇다고 해서 충돌 패스를 하는것은 아니다. 
player에 속해있는 객체도 롤백해야한다. 
*/
void Player::occur_collision(Actor* subject){
    // 하위객체도 롤백
    for(auto const& obj : this->sub_objects){
        obj->rollback_pos();
    }
    this->rollback_pos();
    int collision_layer = subject->collision->get_layer(); 
    if(collision_layer==MONSTER_LAYER){
        if(this->is_invincible){
            return; 
        }
        this->is_invincible = true;
    }
    
    mvprintw(1, 30, "Num Of COLLISION! %d", this->test);
    this->test+=1;
    refresh();
}

bool Player::get_invincible(){
    return this->is_invincible;
}