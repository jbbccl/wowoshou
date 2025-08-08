extends Node


func _on_Player_debug_information(node, new_pos):
	print("The position of " + node.name + " is now " + str(new_pos))

