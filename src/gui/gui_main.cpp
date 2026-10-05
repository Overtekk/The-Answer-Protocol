/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:13:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 16:27:44 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <typeinfo>
# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/PNJ.hpp"
# include "base_class/items/Weapon.hpp"

int main() {
    // SetConfigFlags(FLAG_VSYNC_HINT);
	// InitWindow(800, 450, "raylib example - basic window");
    // SetTargetFPS(60);

	VisualPlayer kris("Kris", "assets/sprites/player/kris_walk.png", {19, 38}, 20, 2.0f);

    PNJ ralsei("Ralsei", "None/None/stil/None",100);

    std::unique_ptr wooden_sword = std::make_unique<Weapon>("Wooden Sword", "t");

    Room room1("Spawn", "I don't have any description yet", "assets/sprites/player/kris_walk.png", false, false);
    
    room1.addPlayer(&kris);
    std::cout << room1.getPlayer(kris.getName())->getName() << "\n\n";
    room1.popPlayer("Kris");

    room1.addPNJ(&ralsei);
    std::cout << room1.getPNJ("Ralsei")->getName() << "\n\n";
    room1.popPNJ("Ralsei");

    room1.placeItem(wooden_sword.get());
    std::cout << room1.getItem(wooden_sword->getId())->getName() << "\n\n";

    // le pointeur est de type Item, mais la valeur reste un Weapon
    Item *ptr = room1.popItem(wooden_sword->getId());
    std::cout << typeid(*ptr).name() << "\n";
    

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
