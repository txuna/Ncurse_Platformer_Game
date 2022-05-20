#include "main.h"

Player::Player(int ypos, int xpos, chtype texture)
    :Actor(ypos, xpos, texture)
{
    velocity = new Velocity(0, 0);
}

Player::~Player(){
    delete velocity;
}
//여기에 키 입력?
// 매 프레임마다 업데이트 Godot을 치면 _process 느낌
void Player::update(){
    this->velocity->x = 0;
    if(kbhit()){
        int ch = getch();
        // if is_on_floor()  
        if(ch == KEY_UP){
            if(!this->is_jump && this->is_floor){
                this->is_jump = true;
            }
        }
        if(ch == KEY_LEFT){
            this->velocity->x = -1; 
        }
        if(ch == KEY_RIGHT){
            this->velocity->x = 1;
        }
    }
    if(is_jump){
        this->velocity->y = -JUMP;
        is_jump = false;
    }else{
        //중력 적용
        if(this->ypos + this->velocity->y < 18){
            this->velocity->y = GRAVITY;
            this->is_floor = false;
            //this->velocity->y += GRAIVITY; // 원래는 이건데 터미널은 소수점을 표현못해서 ㅎㅎ
        }else{
            this->velocity->y = 0;
            this->is_floor = true;
        }
    }



    this->actor_move(this->velocity);
}

void Player::draw(){

}