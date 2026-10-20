/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/20 15:33:12 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <poll.h>
# include <csignal>
# include <iostream>
# include <string.h>

# include "raylib.h"
# include "gui/data/VisualWorldState.hpp"
# include "gui/entities/User.hpp"
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

# include "gui/connection/ServerLink.hpp"
# include "common.h"

int 	gui_parser(WorldConfig& world_config);
void 	graphic(WorldConfig& world_config, int argc, char** argv);
void 	print_server_sends(const std::vector<std::string> &lines);


int main(int argc, char** argv) {
	WorldConfig world_config;
	if (gui_parser(world_config) == 0)
	{
		graphic(world_config, argc, argv);
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

void graphic(WorldConfig& world_config, int argc, char** argv)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);

	ServerLink			connection(argc, argv);
	
	LoadedAssets		assets;
	LoadAssets(world_config, assets);
	VisualWorldState	data("Kris", assets.sprites.at("player"), std::make_tuple(19, 38), 2.0f, assets);
	
	// std::cout << "============================================\n";
	VisualItemWeapon*		sword = data.getAddWeapon("wooden_sword");
	VisualItemConsumable*	v_cookie = data.getAddConsumable("COOKIE");
	bool					Icon = false;

	connection.send_commande("CONNECT Nomi");
	data.user->setPos(Vector2 {400, 225});
	sword->setPos(Vector2 {500, 225});
	v_cookie->setPos(Vector2 {150, 150});

    while (!WindowShouldClose())
    {
		print_server_sends(connection.recive());

        BeginDrawing();
            ClearBackground(BLACK);

			sword->DrawInRoom();
			v_cookie->DrawInRoom();
			if (Icon == true)
			{
				sword->DrawWeaponIcon(495, 180);
			}
			
			data.user->update();
			data.user->onDraw();

			if (IsKeyReleased(KEY_E))
			{
				if (checkCollison(data.user->getPos().x, data.user->getPos().y, data.user->getWidth(), data.user->getHeight(), sword->getPos().x, sword->getPos().y, sword->getChestWidth(), sword->getChestHeight()))
				{
					sword->ItemPicked();
					Icon = true;
					connection.send_commande("LOOK");
				}
			}

        EndDrawing();
    }

	UnloadAssets(assets);
    CloseWindow();
}

void print_server_sends(const std::vector<std::string> &lines)
{
	for (auto line : lines) {
		std::cout << line << "\n==================================\n";
	}
}
