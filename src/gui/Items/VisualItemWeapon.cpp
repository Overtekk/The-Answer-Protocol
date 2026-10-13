/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemWeapon.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:38:04 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/13 15:18:45 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/Items/VisualItemWeapon.hpp"

VisualItemWeapon::VisualItemWeapon(
    const Item &item,
	const LoadedAssets &assets,
	float sprite_scale
):
	VisualItem(item, assets, sprite_scale),
	_obj_texture(assets.sprits.at("ItemsIcons")) {}

void VisualItemWeapon::DrawWeaponIcon(float x, float y, float width, float height)
    {
        if (width < 0)
            width = this->_OBJ_WIDTH;
        if (height < 0)
            height = this->_OBJ_HEIGHT;

        Rectangle src = Rectangle{
            .x = 0,
            .y = 0,
            .width = (float)this->_OBJ_WIDTH,
            .height = (float)this->_OBJ_HEIGHT
        };

        Rectangle dest = Rectangle{
            .x = x,
            .y = y,
            .width = width * this->_sprite_scale,
            .height = height * this->_sprite_scale,
        };

        DrawTexturePro(this->_obj_texture, src, dest, {width / 2, height / 2}, 0, WHITE);
    }