/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:00:27 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/19 14:26:40 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unordered_map>
# include <string>

# include "raylib.h"
# include "gui/VisualRoom.hpp"
# include "gui/Items/VisualItem.hpp"


VisualRoom::VisualRoom(
    const Texture2D	&tile_map
):
    tile_map(tile_map)
{}

void	VisualRoom::drawItems()
{
    for (auto item : this->items) {
        item.second->DrawInRoom();
    }
}