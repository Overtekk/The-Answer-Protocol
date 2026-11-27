/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/27 13:57:31 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <string>
# define HOXML_IMPLEMENTATION
# define RAYTMX_IMPLEMENTATION
#include "raytmx.h"
#include <cstddef>

# include <poll.h>
# include <csignal>
# include <iostream>
# include <string.h>

# include "raylib.h"
# include "gui/rooms/RoomManager.hpp"
# include "gui/GameCamera.hpp"
# include "gui/data/VisualWorldState.hpp"
# include "gui/entities/User.hpp"
# include "gui/HUD/TextBoxs/TextBoxManager.hpp"
# include "gui/HUD/TextBoxs/AutoTextBox.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/Items/VisualItemConsumable.hpp"
# include "base_class/entities/NPC.hpp"
# include "base_class/items/ItemWeapon.hpp"
# include "base_class/items/ItemConsumable.hpp"
# include "config/LoadedAssets.hpp"
# include "config/Enums.hpp"
# include "config/config.hpp"
# include "config/config_messages.h"
# include "parser.h"
# include "gui.h"

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
	YAML::Node root = load_file(DATA_PATH);
	YAML::Node root_sounds = load_file(DATA_SOUNDS_PATH);
	YAML::Node root_sprites = load_file(DATA_SPRITES_PATH);
	if (root.IsNull() or root_sounds.IsNull() or root_sprites.IsNull())
		return EXIT_FAILURE;

	std::queue<YAML::Node> nodes_list;
	nodes_list.push(root);
	nodes_list.push(root_sounds);
	nodes_list.push(root_sprites);

	if (!parse_file_for_gui(nodes_list, world_data)) {
		std::cerr << INVALID_DATA;
		return 1;
	 }

	 return 0;
}


void graphic(WorldConfig& world_config, int argc, char** argv)
{
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);
	// const float panSpeed = 150.0f;

	ServerLink			connection(argc, argv);

	LoadedAssets		assets;
	LoadAssets(world_config, assets);
	VisualWorldState	data("Kris", assets.sprites.at("player"), std::make_tuple(19, 38), 1.0f, assets);
	RoomManager			room(data, connection, data.user.get());
	// initiat the texture for the singleton TextBoxManager Class
	TextBoxManager::access().loadAssets(assets);

	connection.send_commande("CONNECT Nomi", Commande::CONNECT);

	data.user->giveRoomManager(&room);
	data.user->setPos(Vector2 {400, 225});

	GameCamera			camera(data.user.get(), data.user->getPos(), 2.0);

	// Connect the player
	while (connection.connect("Nomi") == false) {
		connection.recive();
	}

	// Setup the first room
	connection.send_commande("LOOK --details", Commande::LOOK);
	while (room.updateRoomState() == false) {
		connection.recive();
	}

	// TextBoxManager::access().addTextBox<AutoTextBox>("Test Cedric"); <-- textBox exemple

    while (!WindowShouldClose())
    {
		connection.recive();
		camera.update(room.getCurrentRoom());
		TextBoxManager::access().updatedTextBoxes();

		room.updateRoom();
		data.user->debug_orientation();
		if (TextBoxManager::access().boxQueuEmpty()){
			data.user->update();
		}

        BeginDrawing();
            ClearBackground(BLACK);

			BeginMode2D(*camera.getCamera());
			{
				room.drawRoom(&camera);
				data.user->onDraw();
				data.user->draw_foot();
			}
			EndMode2D();

			TextBoxManager::access().drawTextBoxes();

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
