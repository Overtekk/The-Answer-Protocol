/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/10/05 14:30:24 by roandrie         ###   ########.fr       */
=======
/*   Updated: 2026/10/05 16:27:44 by nbuchy           ###   ########.fr       */
>>>>>>> 1a70e55f679b227fb87869be1117c7eb3399c765
/*                                                                            */
/* ************************************************************************** */

#include <typeinfo>
# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
<<<<<<< HEAD
# include "gui.h"
# include "utils.h"
# include "debug.h"

int gui_parser();
#include "gui/entities/VisualPlayer.hpp"
=======
>>>>>>> 1a70e55f679b227fb87869be1117c7eb3399c765
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/PNJ.hpp"
# include "base_class/items/Weapon.hpp"

int main() {
    // SetConfigFlags(FLAG_VSYNC_HINT);
	// InitWindow(800, 450, "raylib example - basic window");
    // SetTargetFPS(60);

	gui_parser();

    VisualPlayer kris("Kris", "assets/sprites/player/kris_walk.png", {19, 38}, 20, 2.0f);

    PNJ ralsei("Ralsei", "None/None/stil/None",100);

    std::unique_ptr wooden_sword = std::make_unique<Weapon>("Wooden Sword", "t");

    Room room1("Spawn", "I don't have any description yet", "assets/sprites/player/kris_walk.png", false, false);

    room1.addPlayer(&kris);
    std::cout << room1.getPlayer(kris.getName())->getName() << "\n\n";
    room1.popPlayer("Kris");

<<<<<<< HEAD
=======
    room1.addPNJ(&ralsei);
    std::cout << room1.getPNJ("Ralsei")->getName() << "\n\n";
    room1.popPNJ("Ralsei");

    room1.placeItem(wooden_sword.get());
    std::cout << room1.getItem(wooden_sword->getId())->getName() << "\n\n";

    // le pointeur est de type Item, mais la valeur reste un Weapon
    Item *ptr = room1.popItem(wooden_sword->getId());
    std::cout << typeid(*ptr).name() << "\n";
    
>>>>>>> 1a70e55f679b227fb87869be1117c7eb3399c765

    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();
    //         ClearBackground(RAYWHITE);

	// 		kris.update(GetFrameTime());
	// 		kris.on_draw();

    //     EndDrawing();
    // }

    // CloseWindow();

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

	 debug_print_structure(world_data, true);
	 return 0;
}
