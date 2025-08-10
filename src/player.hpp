#ifndef PLAYER_H
#define PLAYER_H

#include <AnimatedSprite.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <InputEventMouseButton.hpp>
#include <Viewport.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>


class Player : public godot::Area2D {
	GODOT_CLASS(Player, godot::Area2D)

	godot::AnimatedSprite *_animated_sprite;
	godot::CollisionShape2D *_collision_shape_head;
    godot::CollisionShape2D *_collision_shape_body;

	//场景
	godot::Ref<godot::PackedScene> shou_sence;
	
	godot::Input *_input;
	godot::Viewport* _viewport;
	godot::ResourceLoader* _resourceLoader;
	godot::Vector2 _screen_size; // Size of the game window.

private:
	bool toward;
public:
	real_t speed = 400; // How fast the player will move (pixels/sec).

	void _init(){}
	void _ready();
	void _process(const double p_delta);
	void start(const godot::Vector2 p_position);
	void _on_Player_body_entered(godot::Node2D *_body);

	static void _register_methods();

	void spawn_shou(godot::Vector2 pos);
};

#endif 
