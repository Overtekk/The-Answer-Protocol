/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:45:11 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/22 10:56:54 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unordered_map>
# include <string>

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"

class VisualRoom
{
    private:
        std::unordered_map<std::string, VisualItem*>	items;

		Texture2D										tile_map;
    public:
        VisualRoom(
			const Texture2D	&tile_map
		);

        ~VisualRoom() = default;

        void    										addItem(VisualItem *item, const std::string &id);

		std::unordered_map<std::string, VisualItem*>	&getItems();
        
		void											drawItems();

		void											shutUp() { std::ignore = this->tile_map; }
};
