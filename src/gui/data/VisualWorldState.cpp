/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualWorldState.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:34:47 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/19 14:36:02 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <unordered_map>
# include <memory>

# include "gui/data/VisualWorldState.hpp"

# include "gui/VisualRoom.hpp"

# include "gui/entities/VisualEntity.hpp"
# include "gui/entities/VisualPlayer.hpp"
# include "gui/entities/User.hpp"

# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/Items/VisualItemKey.hpp"
# include "gui/Items/VisualItemConsumable.hpp"

# include "config/LoadedAssets.hpp"


VisualWorldState::VisualWorldState(
	const std::string &id,
	const Texture2D &texture,
	std::tuple<int, int> sprite_dim,
	float scale,
	const LoadedAssets &assets
):
    assets(assets),
    user(std::make_unique<User>(id, texture, sprite_dim, scale))
{
    for (auto room_tile_map: assets.tile_maps) {
        this->rooms.emplace(room_tile_map.first, std::make_unique<VisualRoom>(room_tile_map.second));
    }
}

VisualItem*			VisualWorldState::getAddItem(const std::string &id) {
    try { return (this->items.at(id).get()); }
    catch(...)
    {
        this->items.emplace(id, std::make_unique<VisualItem>(id, this->assets, 2.0f));
		return (this->items.at(id).get());
    }
}

VisualItemWeapon*	VisualWorldState::getAddWeapon(const std::string &id)
{
	try { return ((VisualItemWeapon *)this->items.at(id).get()); }
    catch(...)
    {
        this->items.emplace(id, std::make_unique<VisualItemWeapon>(id, this->assets, 2.0f));
		return ((VisualItemWeapon *)this->items.at(id).get());
    }
}

VisualItemKey*		VisualWorldState::getAddKey(const std::string &id)
{
	try { return ((VisualItemKey *)this->items.at(id).get()); }
    catch(...)
    {
        this->items.emplace(id, std::make_unique<VisualItemKey>(id, this->assets, 2.0f));
		return ((VisualItemKey *)this->items.at(id).get());
    }
}

VisualItemConsumable*	VisualWorldState::getAddConsumable(const std::string &id)
{
	try { return ((VisualItemConsumable *)this->items.at(id).get()); }
    catch(...)
    {
        this->items.emplace(id, std::make_unique<VisualItemConsumable>(id, this->assets, 2.0f));
		return ((VisualItemConsumable *)this->items.at(id).get());
    }
}