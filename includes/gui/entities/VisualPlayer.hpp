/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:48:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 11:16:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "base_class/entities/Player.hpp"
# include "gui/entities/VisualEntity.hpp"

class VisualPlayer : public Player, public VisualEntity {
	public:
		VisualPlayer(
			const std::string& name,
			const fs::path& sprite,
			std::tuple<int, int> sprite_dim,
			int health,
			float scale = 1.0f
		) : Player(name, sprite, health),
			VisualEntity(*this, sprite_dim, scale) {}

	private:
		virtual void update_movement(float delta_time) override;
};
