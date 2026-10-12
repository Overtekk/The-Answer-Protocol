/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItem.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 15:27:08 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/12 16:42:14 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"
# include "gui/Animation.hpp"


VisualItem::VisualItem(
    const Item &item,
	const Texture2D &obj_texture,
	std::tuple<float, float> obj_size,
	const Texture2D &chest_texture,
	float sprite_scale
):
    _item(item),
    _obj_texture(obj_texture),
    _obj_size(obj_size),
    _chest_sprits(Animation(chest_texture, {42, 20}, 2, 2, 0, 0.0f, false)),
    _sprite_scale(sprite_scale) {}

    void VisualItem::DrawInRoom()
    {
        this->_chest_sprits.drawCurentFrame(this->_position.x, this->_position.y);
    }

    void VisualItem::DrawItem(float x, float y, float width, float height)
    {
        if (width < 0)
            width = std::get<0>(this->_obj_size);
        if (height < 0)
            height = std::get<1>(this->_obj_size);

        Rectangle src = Rectangle{
            .x = 0,
            .y = 0,
            .width = std::get<0>(this->_obj_size),
            .height = std::get<1>(this->_obj_size)
        };

        Rectangle dest = Rectangle{
            .x = x,
            .y = y,
            .width = width * this->_sprite_scale,
            .height = height * this->_sprite_scale,
        };

        DrawTexturePro(this->_obj_texture, src, dest, {width / 2, height / 2}, 0, WHITE);
    }
