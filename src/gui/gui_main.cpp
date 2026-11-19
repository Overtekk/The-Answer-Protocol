/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/19 09:33:12 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define HOXML_IMPLEMENTATION
# define RAYTMX_IMPLEMENTATION

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
	const float panSpeed = 150.0f;

	ServerLink			connection(argc, argv);

	LoadedAssets		assets;
	LoadAssets(world_config, assets);
	VisualWorldState	data("Kris", assets.sprites.at("player"), std::make_tuple(19, 38), 2.0f, assets);
	RoomManager			room(data, connection, data.user.get());

	connection.send_commande("CONNECT Nomi", Commande::CONNECT);

	data.user->setPos(Vector2 {400, 225});

	Camera2D			camera;
	camera.target = Vector2{data.user->getPos().x, data.user->getPos().y};
	camera.offset = Vector2{GetRenderWidth()/2.0f, GetRenderHeight()/2.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	// Connect the player
	while (connection.connect("Nomi") == false) {
		connection.recive();
	}

	// Setup the first room
	connection.send_commande("LOOK --details", Commande::LOOK);
	while (room.updateRoomState() == false) {
		connection.recive();
	}

    while (!WindowShouldClose())
    {
		connection.recive();
		if (IsKeyDown(KEY_D)) camera.target.x += panSpeed*GetFrameTime();
        if (IsKeyDown(KEY_A)) camera.target.x -= panSpeed*GetFrameTime();
        if (IsKeyDown(KEY_S)) camera.target.y += panSpeed*GetFrameTime();
        if (IsKeyDown(KEY_W)) camera.target.y -= panSpeed*GetFrameTime();

		room.updateRoom();
		data.user->update();

        BeginDrawing();
            ClearBackground(BLACK);
			BeginMode2D(camera);
			{
				DrawTMX(room.getCurrentRoom()->getTileMap(), &camera, NULL, 0, 0, WHITE);
				room.drawRoom();
			}
			EndMode2D();
			
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
