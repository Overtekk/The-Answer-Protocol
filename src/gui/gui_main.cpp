/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/12 15:07:16 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <typeinfo>

# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/NPC.hpp"
# include "base_class/items/ItemWeapon.hpp"
# include "config/LoadedAssets.hpp"
# include "parser.h"
# include "gui.h"
# include "utils.h"
# include "debug.h"

int gui_parser(WorldConfig& world_data);
void graphic(WorldConfig& world_data);


int main() {
	WorldConfig world_data;
	gui_parser(world_data);

	// room_tester();
	graphic(world_data);
    return 0;
}

int gui_parser(WorldConfig& world_data) {
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

void graphic(WorldConfig& world_data)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);

	LoadedAssets	assets;
	LoadAssets(world_data, assets);
	
	Animation		test_animation(assets.sprits["player"], {19, 38}, 4, 12, 0, 0.18f, false); // loop is disabled
	Player			kris("Kris");
    VisualPlayer 	v_kris(kris, "assets/sprites/player/kris_walk.png", {19, 38}, 2.0f);

	v_kris.setPos(Vector2 {400, 225});

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

			v_kris.update();
			v_kris.onDraw();

			test_animation.playAnimation(50, 50, 2, false, 90.0);

        EndDrawing();
    }

	UnloadAssets(assets);
    CloseWindow();
}
