/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:48:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 15:16:08 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <algorithm>
# include "base_class/entities/Player.hpp"
# include "gui/entities/VisualEntity.hpp"

class VisualPlayer : public VisualEntity {
	private:
		std::vector<int> 	_activeKeys;
		int 				_keys[8] = {KEY_UP, KEY_W ,KEY_DOWN, KEY_S ,KEY_LEFT, KEY_A ,KEY_RIGHT, KEY_D};

		virtual void updateMovement() override;

	public:
		VisualPlayer(
			const Player& player, // player inherit from entity so it's ok to pass player to VisualEntity
			const std::string texture,
			std::tuple<int, int> sprite_dim,
			float scale
		);
};
