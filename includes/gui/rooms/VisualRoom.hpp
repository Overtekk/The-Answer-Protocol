/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:45:11 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/16 16:41:17 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unordered_map>
# include <string>
# include <tuple>

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"

class VisualRoom
{
    private:
        std::unordered_map<std::string, VisualItem*>	items;

		Texture2D										tile_map;
        std::tuple<int, int>                            size;
    public:
        const std::string                               name;

        VisualRoom(
			const Texture2D	&tile_map,
            const std::string name
		);

        ~VisualRoom() = default;

        // Add any type of item to the room
        void    										addItem(VisualItem *item, const std::string &id);

        // Get a dict of all items in the room
		std::unordered_map<std::string, VisualItem*>	&getItems();
        
        // Return room width
        int                                             getWidth();
        // Return room height
        int                                             getHeight();
        
        // draw the room and its items
		void											drawItems();

		void											shutUp() { std::ignore = this->tile_map; }
};
