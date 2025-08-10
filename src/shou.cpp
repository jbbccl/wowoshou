#include "shou.hpp"

//在这个文件nn生成手
void Player::spawn_shou(godot::Vector2 pos){
    if(shou==nullptr){
        if (shou_sence.is_valid()){
            shou = shou_sence->instance();
            add_child(shou);
        }
    }else{
        //跟随手
        if(pos.length()>shou_dist){
            pos=pos.normalized()*shou_dist;
        }
        
        shou->set("position", pos);
    }

}