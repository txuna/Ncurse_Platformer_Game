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
            if(!is_jump){
                is_jump = true;
            }
        }
        if(ch == KEY_LEFT){
            this->velocity->x = -1; 
        }
        if(ch == KEY_RIGHT){
            this->velocity->x = 1;
        }
    }
    // 임시적인 변수 velocity를 두고 actor_move에서 충돌체크하고 실질적으로 움직일 수 있는지 확인
    // 중력 적용
    if(this->ypos + this->velocity->y < 18){
        this->velocity->y = GRAVITY;
        //this->velocity->y += GRAIVITY; // 원래는 이건데 터미널은 소수점을 표현못해서 ㅎㅎ
    }else{
        this->velocity->y = 0;
    }
    this->actor_move(this->velocity);
}

void Player::draw(){

}