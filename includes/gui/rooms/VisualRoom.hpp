/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:45:11 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/24 10:03:59 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unordered_map>
# include <string>
# include <tuple>

# include "raytmx.h"
# include "gui/Items/VisualItem.hpp"

class VisualRoom
{
    private:
        std::unordered_map<std::string, VisualItem*>	items;

		TmxMap										    *tile_map;
        std::tuple<int, int>                            size;
    public:
        const std::string                               name;

        VisualRoom(
			TmxMap *tile_map,
            const std::string name
		);

        ~VisualRoom() = default;

        // Add any type of item to the room
        void    										addItem(VisualItem *item, const std::string &id);

        // Get a dict of all items in the room
		std::unordered_map<std::string, VisualItem*>	&getItems();
        // Clean the items dict of the room
        void                                            RemoveAllItems();
        
        // Return room width
        int                                             getWidth();
        // Return room height
        int                                             getHeight();
        
        // Draw the room and its items
		void											drawItems();

        // Drwe room .... I think ?
		void											drawRoom();

		TmxMap                                          *getTileMap();
};
