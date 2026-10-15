/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualPlayer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:07:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/15 16:09:36 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gui/entities/VisualPlayer.hpp"

VisualPlayer::VisualPlayer(
			const std::string id, // player inherit from entity so it's ok to pass player to VisualEntity
			const Texture2D &texture,
			std::tuple<int, int> sprite_dim,
			float scale
) : VisualEntity(id, texture, sprite_dim, scale) {}

void	VisualPlayer::updateMovement() {}