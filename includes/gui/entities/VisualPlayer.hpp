/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:48:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/15 16:12:52 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <algorithm>
# include "gui/entities/VisualEntity.hpp"

class VisualPlayer : public VisualEntity {
	public:
		VisualPlayer(
			const std::string id, // player inherit from entity so it's ok to pass player to VisualEntity
			const Texture2D &texture,
			std::tuple<int, int> sprite_dim,
			float scale
		);

	void updateMovement() override;
};
