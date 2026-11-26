/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItem.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:42:22 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 11:40:31 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>

# include "raylib.h"
# include "gui/Animation.hpp"
# include "config/LoadedAssets.hpp"

class VisualItem
{
    protected:
		std::string					_id;
        Vector2						_position = {0.0f, 0.0f};
		const int					_CHEST_WIDTH = 20.0f;
		const int					_CHEST_HEIGHT = 20.0f;
        Animation					_chest_sprits; // chest is for the item placed on the room
	
		Rectangle 					_item_box; // used for collision
		float						_sprite_scale;
    public:
        VisualItem(
			const std::string &id,
			const LoadedAssets &assets,
			float sprite_scale);

        ~VisualItem() = default;

		// Draw item representation when it's in a room (it's a chest)
		void 				DrawInRoom();

		// Retunr a reference to the item object and set the chest sprit to opened
		const std::string 	&ItemPicked();

		// Set object coordinates
		void				setPos(const Vector2 &new_pos);

		// Return object coordinates
		const Vector2& 		getPos() const;

		// return chest sprite Width
		int 				getChestWidth() const;
		
		// return chest sprite Height
		int 				getChestHeight() const;

		// return chest box collision
		const Rectangle 	&getItemBox();
    };
