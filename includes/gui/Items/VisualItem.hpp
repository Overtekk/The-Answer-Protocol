/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItem.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:42:22 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/13 16:32:12 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <tuple>

# include "raylib.h"
# include "gui/entities/VisualPlayer.hpp"
# include "base_class/items/Item.hpp"
# include "gui/Animation.hpp"
# include "config/LoadedAssets.hpp"

class VisualItem
{
    protected:
		// Reference to the item
        const Item&					_item;

        Vector2						_position = {0.0f, 0.0f};
		const int					_CHEST_WIDTH = 20.0f;
		const int					_CHEST_HEIGHT = 20.0f;
        Animation					_chest_sprits; // chest is for the item placed on the room
	
		float						_sprite_scale;
    public:
        VisualItem(const Item &item,
			const LoadedAssets &assets,
			float sprite_scale);

        ~VisualItem() = default;

		// Draw item representation when it's in a room (it's a chest)
		void 	DrawInRoom();

		// Retunr a reference to the item object and set the chest sprit to opened
		const Item &ItemPicked();

		// Set object coordinates
		void	setPos(const Vector2 &new_pos);

		// Return object coordinates
		const Vector2& getPos() const;

		// return chest sprite Width
		int getChestWidth() const;
		
		// return chest sprite Height
		int getChestHeight() const;
    };
