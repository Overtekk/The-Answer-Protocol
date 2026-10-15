/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItem.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 15:27:08 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/15 15:45:53 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"
# include "gui/Animation.hpp"


VisualItem::VisualItem(
    const std::string &id,
	const LoadedAssets &assets,
	float sprite_scale
):
    _id(id),
    _chest_sprits(Animation(assets.sprits.at("chest"),
                            {this->_CHEST_WIDTH, this->_CHEST_HEIGHT,},
                            2, 2, 0, 0.0f, false)),
    _sprite_scale(sprite_scale) {}

    void VisualItem::DrawInRoom()
    {
        this->_chest_sprits.drawCurentFrame(this->_position.x, this->_position.y, this->_sprite_scale);
    }
    
const std::string& VisualItem::ItemPicked()
{
    this->_chest_sprits.setFrame(1);
    return (this->_id);
}

void VisualItem::setPos(const Vector2 &new_pos)
{
    this->_position = new_pos;
}

const Vector2& VisualItem::getPos() const
{
    return (this->_position);
}

int VisualItem::getChestWidth() const
{
    return (this->_CHEST_WIDTH);
}

int VisualItem::getChestHeight() const
{
    return (this->_CHEST_HEIGHT);
}
