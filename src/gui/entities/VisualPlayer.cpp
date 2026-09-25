/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:07:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 11:38:08 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gui/entities/VisualPlayer.hpp"

void VisualPlayer::update_movement(float) {
	int x = 0;
	int y = 0;

	if (IsKeyDown(KEY_UP) or IsKeyDown(KEY_W)) {
		y = -1;
	}
	if (IsKeyDown(KEY_DOWN) or IsKeyDown(KEY_S)) {
		y = +1;
	}
	if (IsKeyDown(KEY_LEFT) or IsKeyDown(KEY_A)) {
		x = -1;
	}
	if (IsKeyDown(KEY_RIGHT) or IsKeyDown(KEY_D)) {
		x = +1;
	}
	set_direction(x, y);
}
