/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/13 16:31:35 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <typeinfo>

# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/Items/VisualItemConsumable.hpp"
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/NPC.hpp"
# include "base_class/items/ItemWeapon.hpp"
# include "base_class/items/ItemConsumable.hpp"
# include "config/LoadedAssets.hpp"
# include "config/Enums.hpp"
# include "parser.h"
# include "gui.h"
# include "utils.h"
# include "debug.h"

int gui_parser(WorldConfig& world_data);
void graphic(WorldConfig& world_data);


int main() {
	WorldConfig world_data;
	if (gui_parser(world_data) == 0)
	{
		graphic(world_data);
		return (0);
	}
	return (1);
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

bool checkCollison(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if ((x1 + w1 / 2 > x2 - w2 / 2 and x1 - w1 / 2 < x2 + w2 / 2)
	and (y1 + h1 / 2 > y2 - h2 / 2 and y1 - h1 / 2 < y2 + h2 / 2))
		return (true);
	return (false);
}

void graphic(WorldConfig& world_data)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);

	LoadedAssets	assets;
	LoadAssets(world_data, assets);
	
	// Animation		test_animation(assets.sprits["player"], {19, 38}, 4, 12, 0, 0.18f, false); // loop is disabled
	ItemWeapon			sword("001", "basic sword", "The most basic sword ever", ItemType::WEAPON, 10, 10);
	ItemConsumable		cookie("001", "basic sword", "The most basic sword ever", ItemType::WEAPON, 10, 10);
	VisualItemWeapon	v_sword(sword, assets, 2.0f);
	VisualItemConsumable	v_cookie(cookie, assets, 2.0f);
	bool				Icon = false;
	Player				kris("Kris");
    VisualPlayer 		v_kris(kris, "assets/sprites/player/kris_walk.png", {19, 38}, 2.0f);

	v_kris.setPos(Vector2 {400, 225});
	v_sword.setPos(Vector2 {500, 225});
	v_cookie.setPos(Vector2 {150, 150});

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

			v_sword.DrawInRoom();
			v_cookie.DrawInRoom();
			if (Icon == true)
			{
				v_sword.DrawWeaponIcon(495, 180);
			}
			
			v_kris.update();
			v_kris.onDraw();

			if (IsKeyReleased(KEY_E))
			{
				if (checkCollison(v_kris.getPos().x, v_kris.getPos().y, v_kris.getWidth(), v_kris.getHeight(), v_sword.getPos().x, v_sword.getPos().y, v_sword.getChestWidth(), v_sword.getChestHeight()))
				{
					v_sword.ItemPicked();
					Icon = true;
				}
			}

			// test_animation.playAnimation(50, 50, 2, false, 90.0);
        EndDrawing();
    }

	UnloadAssets(assets);
    CloseWindow();
}
