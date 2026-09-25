/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 11:31:01 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
#include "gui/entities/VisualPlayer.hpp"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 450, "raylib example - basic window");
    SetTargetFPS(60);

	VisualPlayer kris("Kris", "assets/sprites/player/kris_walk.png", {19, 38}, 20, 2.0f);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

			kris.update(GetFrameTime());
			kris.on_draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
