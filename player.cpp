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
    bool is_move = false;
    if(kbhit()){
        int ch = getch(); 
        /*
        if(ch == KEY_UP){
            if(!is_jump){
                is_jump = true;
                 this->backup_pos(); 
            }
        }
        if(ch == KEY_DOWN){
            this->backup_pos();
            this->ypos += 1;
        }
        if(ch == KEY_LEFT){
            this->backup_pos();
            this->xpos -= 1; 
        }
        if(ch == KEY_RIGHT){
            this->backup_pos();
            this->xpos += 1; 
        }*/
        switch(ch){
            case KEY_UP:
                if(!is_jump){
                    is_jump = true;
                    this->backup_pos(); 
                }
                break; 
            
            case KEY_DOWN:
                if(this->ypos +1 >= 19){
                    break;
                }
                this->backup_pos();
                this->ypos += 1;
                is_move = true;
                break; 

            case KEY_LEFT:
                this->backup_pos(); 
                this->xpos -= 1; 
                is_move = true;
                break; 

            case KEY_RIGHT:
                this->backup_pos(); 
                this->xpos += 1; 
                is_move = true;
                break; 

            default:
                break; 
        }
    }
    // 한턴에 한번만 움직임 가능
    if(is_move){
        return;
    }
    if(is_jump){
        if(this->jump_height >= 5){
            is_jump = false; 
            this->jump_height = 0; 
        }
        this->backup_pos(); 
        this->ypos-=1;
        this->jump_height += 1;
    }else{
        if(this->ypos+1<19){
            this->backup_pos(); 
            this->ypos+=1;
        }
    }
}

void Player::draw(){

}