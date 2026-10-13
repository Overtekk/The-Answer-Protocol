/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:07:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 15:16:15 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gui/entities/VisualPlayer.hpp"

VisualPlayer::VisualPlayer(
			const Player& player, // player inherit from entity so it's ok to pass player to VisualEntity
			const std::string texture,
			std::tuple<int, int> sprite_dim,
			float scale
) : VisualEntity(player, texture, sprite_dim, scale) {}

void VisualPlayer::updateMovement()
{
// listen for keys pressed
    for (int k : _keys) {
		// add the key to the stack if it's not already in stack
        if (IsKeyPressed(k) && std::count(_activeKeys.begin(), _activeKeys.end(), k) <= 0) {
            _activeKeys.push_back(k); // add it to the end
        }
    }

    // listen for keys released
    for (int k : _keys) {
		// remove the key from the stack
        if (IsKeyReleased(k) && std::count(_activeKeys.begin(), _activeKeys.end(), k) > 0) {
			// weird way to remove element (vector is ass)
            _activeKeys.erase(std::remove(_activeKeys.begin(), _activeKeys.end(), k), _activeKeys.end());
        }
    }

    int x = 0, y = 0;

    if (!_activeKeys.empty()) {
		// get the key from the top of the stack (end of the vector)
		int last = _activeKeys.back();

        switch (last) {
            case KEY_UP:  
			case KEY_W:  
				y = -1;
				break;
            case KEY_DOWN:
            case KEY_S:
				y = +1;
				break;
            case KEY_LEFT:
            case KEY_A:
				x = -1;
				break;
            case KEY_RIGHT:
            case KEY_D:
				x = +1;
				break;
        }
    }

    setDirection(x, y);
}