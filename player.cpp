#include "main.h"

Player::Player(int ypos, int xpos, int height, int width, std::string texture, WINDOW* canvas)
    :Actor(ypos, xpos, height, width, texture, canvas)
{
    this->velocity = new Velocity(0, 0);
    this->type = T_NON_WIN;
}

Player::~Player(){
    delete velocity;
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
    if(this->xpos + velocity->x + this->width >= WIDTH
    || this->xpos + velocity->x <= 0){
        velocity->x = 0; 
    }
    this->actor_move(this->velocity);
}

void Player::draw(){
    std::string stuff(this->width, ' ');
    mvwaddstr(this->canvas, this->prev_ypos, this->prev_xpos, stuff.c_str());
    mvwaddstr(this->canvas,  this->ypos, this->xpos, this->texture.c_str());
    mvprintw(1, 1, "(%d:%d)", this->ypos, this->xpos);
    refresh();
}
