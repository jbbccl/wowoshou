#include "shou.hpp"

//在这个文件nn生成手
void Player::spawn_shou(godot::Vector2 player_pos,godot::Vector2 mouse_pos){
    if(shou==nullptr){
        if (shou_sence.is_valid()){
            godot::Node *shou_node = shou_sence->instance();
            shou = godot::Object::cast_to<godot::Node2D>(shou_node);//转NODE2D
            add_child(shou);
            shou_dist=0;//当前手的相对距离
            shou_reach=120;
        }
    }
    if(shou_dist<shou_reach){
        shou_dist+=20;
    }
    //跟随手
    godot::Vector2 golbal_pos = shou->get_position();
    godot::Vector2 shou_vec = mouse_pos - player_pos;
    if(shou_vec.length()>shou_dist){
        shou_vec=shou_vec.normalized()*shou_dist;
    }
    shou->set("rotation", shou_vec.angle());
    shou->set("position", shou_vec);
    //godot::Godot::print(shou->get_position());
}

void Player::del_shou(godot::Vector2 player_pos,godot::Vector2 mouse_pos){
    if(shou_dist>8){
        shou_dist-=20;

        godot::Vector2 shou_vec = mouse_pos - player_pos;
        godot::Godot::print(shou->get_position());
        shou_vec=shou_vec.normalized();
        shou->set("rotation", shou_vec.angle());
        shou->set("position", shou_vec*shou_dist);
    }else{
        remove_child(shou);
        shou=nullptr;
    }
}

void Shou::_ready(){
    godot::Godot::print("shou_ready");
}


void Shou::_process(double p_delta){
    
}


void Shou::_register_methods() {
    godot::register_method("_process", &Shou::_process);
    godot::register_method("_ready", &Shou::_ready);
}
/*
先在entry.cpp加上shou类
shou.hpp里加上
_register_methods()声明
*/