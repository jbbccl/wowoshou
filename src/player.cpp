#include "player.hpp"


void Player::_ready() {
    _animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
    _collision_shape_head = get_node<godot::CollisionShape2D>("CollisionShape2DHead");
    _collision_shape_body = get_node<godot::CollisionShape2D>("CollisionShape2DBody");
    _input = godot::Input::get_singleton();
    _resourceLoader = godot::ResourceLoader::get_singleton();
    _viewport = get_viewport();
    _screen_size = get_viewport_rect().size;
    //godot::Godot::print("test");
    //节点
    shou_sence = _resourceLoader->load("res://Main/shou.tscn");
    sword_sence = _resourceLoader->load("res://Main/sword.tscn");

    //set_z_index(0);
}


void Player::_process(const double delta) {
    godot::Vector2 velocity(0, 0);

    //移动
	velocity.x = _input->get_action_strength("move_right") - _input->get_action_strength("move_left");
	velocity.y = _input->get_action_strength("move_down") - _input->get_action_strength("move_up");
    godot::Vector2 player_pos = get_position();

	if (velocity.length() > 0) {
		velocity = velocity.normalized() * speed;
        player_pos += velocity * (real_t)delta;
        player_pos.x = godot::Math::clamp(player_pos.x, (real_t)0.0, _screen_size.x);
        player_pos.y = godot::Math::clamp(player_pos.y, (real_t)0.0, _screen_size.y);
        set_position(player_pos);
        //动画
		_animated_sprite->play();
        _animated_sprite->set_animation("default");
        toward=(velocity.x < 0);
        _animated_sprite->set_flip_h(toward);
	} else {
		_animated_sprite->stop();
	}
    
    //点击  
    godot::Vector2 mouse_pos = _viewport->get_mouse_position();
    if(_input->get_action_strength("shou")){
        //godot::Godot::print(shou_vec);
        spawn_shou(player_pos,mouse_pos,delta);
    }else if(shou!=nullptr){
        //u删除手
        del_shou(player_pos,mouse_pos,delta);
    }

    if(_input->get_action_strength("sword")){
        //拔刀 声明于player.hpp，an实现于simple_sword.cpp 下同 
        spawn_sword(delta);
    }else if(shou!=nullptr){
        //u删除刀
        del_sword(delta);
    }


    //emit_signal("debug_information", this, velocity);
}


void Player::_register_methods() {
    godot::register_method("_process", &Player::_process);
    godot::register_method("_ready", &Player::_ready);
    godot::register_property("speed", &Player::speed, (real_t)400.0);
    godot::register_signal<Player>((char *)"debug_information", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}
