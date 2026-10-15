/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualWorldState.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:00:32 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/15 16:22:47 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <unordered_map>
# include <memory>

# include "gui/VisualRoom.hpp"
# include "gui/entities/VisualEntity.hpp"
# include "gui/entities/VisualPlayer.hpp"
# include "gui/Items/VisualItem.hpp"
# include "gui/entities/User.hpp"

struct VisualWorldState {
	std::unordered_map<std::string, VisualRoom>     rooms;
	std::unordered_map<std::string, VisualEntity>   entities;
	std::unordered_map<std::string, VisualPlayer>   players;
	std::unordered_map<std::string, VisualItem>     items;

    User                                            user;
};

