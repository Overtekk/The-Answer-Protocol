/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 10:07:21 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
# include "gui.h"
# include "server.h" // REMOVE LATER
# include "debug.h"

void test_gui_parser(); // REMOVE LATER

int main() {
    // SetConfigFlags(FLAG_VSYNC_HINT);
	// InitWindow(800, 450, "raylib example - basic window");
    // SetTargetFPS(60);

	test_gui_parser(); // REMOVE LATER

	// VisualPlayer kris("Kris", "assets/sprites/player/kris_walk.png", {19, 38}, 20, 2.0f);

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

bool load_file(const std::string& filepath, YAML::Node& root) { // REMOVE LATER
	try {
		root = YAML::LoadFile(filepath);
	}
	catch (const YAML::Exception& e) {
		return false;
	}
	return true;
}

void test_gui_parser() { // REMOVE LATER
	YAML::Node root;
	WorldConfig world_data;

	if (!load_file("data/world_data.yaml", root)) {
        std::cerr << "\n❌ Unable to load YAML file.\n";
        return;
    }

	if (!parse_file_for_gui(root, world_data)) {
		std::cerr << "\n❌ Server aborting: invalid world data configuration.\n";
		return;
	 }

	 debug_print_structure(world_data, true);
}
