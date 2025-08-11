#include "player.hpp"

void Player::spawn_sword(const double delta){
     if(sword==nullptr){
        if (shou_sence.is_valid()){
            //sword_sence初始化于player.cpp _ready()
            godot::Node *sword_node = sword_sence->instance();
            sword = godot::Object::cast_to<godot::Node2D>(sword_node);//转NODE2D
            sword->set_z_index(-1);//放置在身后，玩家图层为0,在player.cpp _ready设置
            sword_offset_vec = godot::Vector2(-12.5,65); //初始位置 player.hpp
            sword_angle_vec = godot::Vector2(1,0);//初始角度x-> y下
            //sword->set("rotation", sword_vec.angle());
            sword->set("position", sword_offset_vec);
            _animated_sprite->play("drowed_sword");
            add_child(sword);
        }
    }//生成结束
    //
    if(drow_sword_progress<3){
        //旋转刀身
        drow_sword_progress += delta;
        drow_sword_progress*=1.2;//TODO但没必要：位运算优化
        sword_angle_vec = godot::Vector2(godot::Math::cos(drow_sword_progress), 
                                        -godot::Math::sin(drow_sword_progress));

        godot::Godot::print(drow_sword_progress);
        sword->set("rotation", sword_angle_vec.angle());

        //偏移刀身
        sword_offset_vec = godot::Vector2(godot::Math::cos(drow_sword_progress)*sword_offset_vec.x - 26*drow_sword_progress*drow_sword_progress, 
                                         godot::Math::sin(drow_sword_progress)*sword_offset_vec.y);
        sword->set("position", sword_offset_vec);
    }   

    

}

void Player::del_sword(const double delta){

}