/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItem.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:42:22 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/12 16:40:18 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <tuple>

# include "raylib.h"
# include "base_class/items/Item.hpp"
# include "gui/Animation.hpp"

class VisualItem
{
    private:
        const Item&	_item;

        Vector2						_position = {0.0f, 0.0f};
        Texture2D					_obj_texture;
		std::tuple<float, float>	_obj_size;
        Animation					_chest_sprits; // chest is for the item placed on the room
		float						_sprite_scale;
    public:
        VisualItem(const Item &item,
			const Texture2D &obj_texture,
			std::tuple<float, float> obj_size,
			const Texture2D &chest_texture,
			float sprite_scale);

        ~VisualItem() = default;

		// Draw item representation when it's in a room (it's a chest)
		void DrawInRoom();

		// Draw item, if x and y are not specified, it will be drew on the item coordinates
		void DrawItem(float x, float y, float width = -1, float height = -1);
    };
