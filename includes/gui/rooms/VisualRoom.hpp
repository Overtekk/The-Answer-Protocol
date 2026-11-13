/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualRoom.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:45:11 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/13 10:28:43 by nbuchy           ###   ########.fr       */
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

        void    										addItem(VisualItem *item, const std::string &id);

		std::unordered_map<std::string, VisualItem*>	&getItems();
        
        int                                             getWidth();
        int                                             getHeight();
        
		void											drawItems();

		void											shutUp() { std::ignore = this->tile_map; }
};
