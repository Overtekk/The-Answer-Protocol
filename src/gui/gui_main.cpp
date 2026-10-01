/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/01 16:35:13 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
#include "gui/entities/VisualPlayer.hpp"
# include "base_class/rooms/Room.hpp"

int main() {
    // SetConfigFlags(FLAG_VSYNC_HINT);
	// InitWindow(800, 450, "raylib example - basic window");
    // SetTargetFPS(60);

	// VisualPlayer kris("Kris", "assets/sprites/player/kris_walk.png", {19, 38}, 20, 2.0f);

    Room room1("Spawn", "I don't have any description yet", "assets/sprites/player/kris_walk.png", false, false);
    std::cout << room1.getName() << "\n";

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
