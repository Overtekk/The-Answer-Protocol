/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:53:32 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <typeinfo>

# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/NPC.hpp"
# include "base_class/items/ItemWeapon.hpp"
# include "parser.h"
# include "gui.h"
# include "utils.h"
# include "debug.h"

int gui_parser();
void room_tester();
void graphic();


int main() {
	gui_parser();

	// room_tester();
	graphic();
    return 0;
}

int gui_parser() {
	WorldConfig world_data;

	YAML::Node root = load_file("data/world_data.yaml");
	YAML::Node root_sounds = load_file("data/sounds_data.yaml");
	YAML::Node root_sprites = load_file("data/sprites_data.yaml");
	if (root.IsNull() or root_sounds.IsNull() or root_sprites.IsNull()) {
		return EXIT_FAILURE;
	}
	std::queue<YAML::Node> nodes_list;
	nodes_list.push(root);
	nodes_list.push(root_sounds);
	nodes_list.push(root_sprites);

	if (!parse_file_for_gui(nodes_list, world_data)) {
		std::cerr << "\n❌ Server aborting: invalid world data configuration.\n";
		return 1;
	 }

	// debug_print_structure(world_data, true);
	 return 0;
}

void graphic()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);

	Player			kris("Kris", 20);
    VisualPlayer 	v_kris(kris, "assets/sprites/player/kris_walk.png", {19, 38}, 2.0f);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

			v_kris.update(GetFrameTime());
			v_kris.on_draw();

        EndDrawing();
    }

    CloseWindow();
}

void room_tester()
{
	gui_parser();

	Player			kris("Kris", 20);
    VisualPlayer 	v_kris(kris, "assets/sprites/player/kris_walk.png", {19, 38}, 2.0f);

    // NPC ralsei("Ralsei", "He like chocolate", "None/None/stil/None",100);

    std::unique_ptr wooden_sword = std::make_unique<ItemWeapon>("Wooden Sword", "t", ItemType::WEAPON, 100000, 0);

    Room room1("Spawn", "I don't have any description yet", "assets/sprites/player/kris_walk.png", false);
    Room room2("Elevator", "It's the Regretevator elevator !!!", "oiia/oiia", false);

	room1.setExitNorth(&room2);
    room1.addPlayer(&kris);
    std::cout << room1.getPlayer(kris.getName())->getName() << "\n\n";

	room2.setExitSouth(&room1);
	std::cout << room2.getFromDirection(Direction::SOUTH)->getName() << "\n\n";
	std::cout << room2.getFromDirection(Direction::EAST) << "\n\n";
}
