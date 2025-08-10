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
    shou_dist=100;
}


void Player::_process(const double delta) {
    godot::Vector2 velocity(0, 0);

    //移动
	velocity.x = _input->get_action_strength("move_right") - _input->get_action_strength("move_left");
	velocity.y = _input->get_action_strength("move_down") - _input->get_action_strength("move_up");
    godot::Vector2 position = get_position();

	if (velocity.length() > 0) {
		velocity = velocity.normalized() * speed;
        position += velocity * (real_t)delta;
        position.x = godot::Math::clamp(position.x, (real_t)0.0, _screen_size.x);
        position.y = godot::Math::clamp(position.y, (real_t)0.0, _screen_size.y);
        set_position(position);
        //动画
		_animated_sprite->play();
        _animated_sprite->set_animation("default");
        toward=(velocity.x < 0);
        _animated_sprite->set_flip_h(toward);
	} else {
		_animated_sprite->stop();
	}
    
    //点击  
    if(_input->get_action_strength("shou")){
        godot::Vector2 mouse_pos = _viewport->get_mouse_position();
        godot::Vector2 shou_vec = mouse_pos-position;
        
        //godot::Godot::print(shou_vec);
        spawn_shou(shou_vec);
    }else{
        //u删除手
    }



    //emit_signal("debug_information", this, velocity);
}

//还是这里？
// void Player::spawn_shou(godot::Vector2 pos){
//     if (shou_sence.is_valid()){
//         godot::Node* shou = shou_sence->instance();
//         add_child(shou);
//         shou->set("position", pos*100);
//     }
// }


void Player::_register_methods() {
    godot::register_method("_process", &Player::_process);
    godot::register_method("_ready", &Player::_ready);
    godot::register_property("speed", &Player::speed, (real_t)400.0);
    godot::register_signal<Player>((char *)"debug_information", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}
