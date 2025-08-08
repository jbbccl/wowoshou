#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot {

class Player : public Area2D {
    GODOT_CLASS(Player, Area2D)

private:
    float time_passed;

public:
    static void _register_methods();

    Player();
    ~Player();

    void _init(); // our initializer called by Godot

    void _process(float delta);
};

}

#endif
