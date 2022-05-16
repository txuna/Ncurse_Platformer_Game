#include "main.h"

Player::Player(int ypos, int xpos, chtype texture)
    :Actor(ypos, xpos, texture)
{

}

Player::~Player(){

}
//여기에 키 입력?
// 매 프레임마다 업데이트 Godot을 치면 _process 느낌
void Player::update(){
    if(kbhit()){
        int ch = getch(); 
        switch(ch){
            /*
                player->move_player();
            */
            case KEY_UP:
                is_jump = true;
                this->prev_xpos = this->xpos;
                this->prev_ypos = this->ypos; 
                break; 
            
            case KEY_DOWN:
                this->prev_xpos = this->xpos;
                this->prev_ypos = this->ypos;
                this->ypos += 1;
                break; 

            case KEY_LEFT:
                this->prev_xpos = this->xpos;
                this->prev_ypos = this->ypos;
                this->xpos -= 1; 
                break; 

            case KEY_RIGHT:
                this->prev_xpos = this->xpos;
                this->prev_ypos = this->ypos;
                this->xpos += 1; 
                break; 

            default:
                break; 
        }
    }
    if(is_jump){
        if(this->jump_height >= 5){
            is_jump = false; 
            this->jump_height = 0; 
        }
        this->prev_ypos = this->ypos;
        this->prev_ypos = this->ypos;
        this->ypos-=1;
        this->jump_height += 1;
    }else{
        if(this->ypos+1<19){
            this->prev_ypos = this->ypos;
            this->prev_ypos = this->ypos;
            this->ypos+=1;
        }
    }
}

void Player::draw(){

}