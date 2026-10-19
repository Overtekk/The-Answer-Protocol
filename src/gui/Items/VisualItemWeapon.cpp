/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemWeapon.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:38:04 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/19 11:52:14 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>

# include "raylib.h"
# include "gui/Items/VisualItemWeapon.hpp"

VisualItemWeapon::VisualItemWeapon(
    const std::string &id,
	const LoadedAssets &assets,
	float sprite_scale
):
	VisualItem(id, assets, sprite_scale),
	_obj_texture(assets.sprites.at("ItemsIcons")) {}

void VisualItemWeapon::DrawWeaponIcon(float x, float y, float width, float height){
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
