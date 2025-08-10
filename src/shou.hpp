#ifndef SHOU_H
#define SHOU_H

#include <AnimatedSprite.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <InputEventMouseButton.hpp>
#include <Viewport.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>

#include "player.hpp"

class Shou : public godot::Area2D {
	GODOT_CLASS(Shou, godot::Area2D)

	godot::AnimatedSprite *_animated_sprite;
	godot::CollisionShape2D *_collision_shape;

private:

public:
	real_t rad = 150; 

	void _init(){}
	void _ready();
	void _process(const double p_delta);

	static void _register_methods();

};

#endif 
