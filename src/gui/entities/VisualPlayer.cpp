/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:07:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 16:02:01 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gui/entities/VisualPlayer.hpp"

// void VisualPlayer::update_movement(float) 
//{
// 	int x = 0;
// 	int y = 0;

// 	if (IsKeyDown(KEY_UP) or IsKeyDown(KEY_W)) {
// 		y = -1;
// 	}
// 	if (IsKeyDown(KEY_DOWN) or IsKeyDown(KEY_S)) {
// 		y = +1;
// 	}
// 	if (IsKeyDown(KEY_LEFT) or IsKeyDown(KEY_A)) {
// 		x = -1;
// 	}
// 	if (IsKeyDown(KEY_RIGHT) or IsKeyDown(KEY_D)) {
// 		x = +1;
// 	}
// 	set_direction(x, y);
// }


void VisualPlayer::update_movement(float)
{
// Détection des pressions
    int keys[] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

    for (int k : keys) {
        if (IsKeyPressed(k) && std::count(activeKeys.begin(), activeKeys.end(), k) <= 0) {
            // Ajouter la touche si elle n'est pas déjà dans la liste
			std::cout << k << " added\n";
            activeKeys.push_back(k);
        }
    }

    // Détection des relâchements
    for (int k : keys) {
        if (IsKeyReleased(k) && std::count(activeKeys.begin(), activeKeys.end(), k) > 0) {
            activeKeys.erase(std::remove(activeKeys.begin(), activeKeys.end(), k), activeKeys.end());
			std::cout << k << " removed\n";
        }
    }

    int x = 0, y = 0;

    if (!activeKeys.empty()) {
        int last = activeKeys.back(); // dernière touche pressée encore active

        switch (last) {
            case KEY_UP:    y = -1; break;
            case KEY_DOWN:  y = +1; break;
            case KEY_LEFT:  x = -1; break;
            case KEY_RIGHT: x = +1; break;
        }
    }

    set_direction(x, y);
}