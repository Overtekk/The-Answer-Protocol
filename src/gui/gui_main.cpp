/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/22 11:16:59 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <poll.h>
# include <csignal>
# include <iostream>
# include <string.h>

# include "raylib.h"
# include "gui/rooms/RoomManager.hpp"
# include "gui/data/VisualWorldState.hpp"
# include "gui/entities/User.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/Items/VisualItemConsumable.hpp"
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
void 	print_server_sends(ServerLink &lines);


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


void graphic(WorldConfig& world_config, int argc, char** argv)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);

	ServerLink			connection(argc, argv);
	
	LoadedAssets		assets;
	LoadAssets(world_config, assets);
	VisualWorldState	data("Kris", assets.sprites.at("player"), std::make_tuple(19, 38), 2.0f, assets);
	RoomManager			room(data, connection, data.user.get());

	connection.send_commande("CONNECT Nomi", Commande::CONNECT);
	
	data.user->setPos(Vector2 {400, 225});
	// Check if the player is correctly connected and update the spawn room
	while (room.updateRoomState() == false) {
		connection.recive();
		if (!connection.lines.empty()) {
			if (connection.lines.front().find("OK CONNECTE") == 0) {
				connection.lines.pop();
				std::cout << "CONNECTED !!!!\n";
			}
		}
	}
	
    while (!WindowShouldClose())
    {
		connection.recive();

        BeginDrawing();
            ClearBackground(BLACK);
			
			room.updateRoom();
			room.drawRoom();

			data.user->update();
			data.user->onDraw();

			// if (IsKeyReleased(KEY_E))
			// {
			// 	if (checkCollison(data.user->getPos().x, data.user->getPos().y, data.user->getWidth(), data.user->getHeight(), sword->getPos().x, sword->getPos().y, sword->getChestWidth(), sword->getChestHeight()))
			// 	{
			// 		sword->ItemPicked();
			// 		Icon = true;
			// 		connection.send_commande("LOOK", Commande::LOOK);
			// 	}
			// }

        EndDrawing();
    }

	UnloadAssets(assets);
    CloseWindow();
}

void print_server_sends(ServerLink &connection)
{
	while(connection.lines.empty() == false) {
		std::cout << "--> " << connection.lines.front() << "\n";
		connection.lines.pop();
	}
}
