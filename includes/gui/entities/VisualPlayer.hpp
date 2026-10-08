/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:48:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 15:46:58 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <algorithm>
# include "base_class/entities/Player.hpp"
# include "gui/entities/VisualEntity.hpp"

class VisualPlayer : public VisualEntity {
	private:
		std::vector<int> activeKeys;

		virtual void update_movement(float delta_time) override;

	public:
		VisualPlayer(
			const Player& player, // player inherit from entity so it's ok to pass player to VisualEntity
			const std::string texture,
			std::tuple<int, int> sprite_dim,
			float scale
		) : VisualEntity(player, texture, sprite_dim, scale) {}
};
