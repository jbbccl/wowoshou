

#include "player.hpp"


void Player::_ready() {
    _animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
    _collision_shape_head = get_node<godot::CollisionShape2D>("CollisionShape2DHead");
    _collision_shape_body = get_node<godot::CollisionShape2D>("CollisionShape2DBody");
    _input = godot::Input::get_singleton();//此处返回空指针，移动到_process了
    _screen_size = get_viewport_rect().size;//此处返回0,0，移动到_process了
    
    //TODO：
    //找到_ready中不能正确取值的n原因
    // godot::Vector2 velocity(0, 0);
    // emit_signal("debug_information", this, velocity);
}


void Player::_process(const double delta) {
    godot::Vector2 velocity(0, 0);

    // if(_input==nullptr){//临时解决——ready不能初始化问题
    //     _input = godot::Input::get_singleton();//移动到此处
    //     _collision_shape_head = get_node<godot::CollisionShape2D>("CollisionShape2DHead");
    //     _collision_shape_body = get_node<godot::CollisionShape2D>("CollisionShape2DBody");
    //     _animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
    // }

	velocity.x = _input->get_action_strength("move_right") - _input->get_action_strength("move_left");
	velocity.y = _input->get_action_strength("move_down") - _input->get_action_strength("move_up");

	if (velocity.length() > 0) {
		velocity = velocity.normalized() * speed;
        godot::Vector2 position = get_position();
        position += velocity * (real_t)delta;
        _screen_size = get_viewport_rect().size;//移动到此处
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

    //emit_signal("debug_information", this, velocity);
}


void Player::_register_methods() {
    godot::register_method("_process", &Player::_process);
    godot::register_method("_ready", &Player::_ready);
    godot::register_property("speed", &Player::speed, (real_t)400.0);
    godot::register_signal<Player>((char *)"debug_information", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}
