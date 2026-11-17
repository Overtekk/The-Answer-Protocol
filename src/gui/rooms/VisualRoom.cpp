/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:00:27 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/17 16:35:15 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unordered_map>
# include <string>
# include <tuple>
# include <iostream>

# include "raytmx.h"

# include "gui/rooms/VisualRoom.hpp"
# include "gui/Items/VisualItem.hpp"
#include "utils.h"


VisualRoom::VisualRoom(
    TmxMap *tile_map,
    const std::string name
):
    tile_map(tile_map),
	size(std::make_tuple(800, 450)),
	name(name)
{}

void    VisualRoom::addItem(VisualItem *item, const std::string &id) {
    auto result = this->items.emplace(id, item);
    if (result.second == false) {
        std::cout << "not added\n";
    }
    else {
        std::cout << "added\n";
    }
}

std::unordered_map<std::string, VisualItem*>	&VisualRoom::getItems() {
    return (this->items);
}

void                                            VisualRoom::RemoveAllItems() {
    this->items.clear();
}

int												VisualRoom::getWidth() {
	return (std::get<0>(this->size));
}

int												VisualRoom::getHeight() {
	return (std::get<1>(this->size));
}

void	VisualRoom::drawItems() {
    for (auto item : this->items) {
        item.second->DrawInRoom();
    }
}

void    VisualRoom::drawRoom() {
    pass;
}
