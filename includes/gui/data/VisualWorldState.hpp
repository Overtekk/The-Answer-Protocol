/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualWorldState.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:35:42 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/24 10:11:34 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unordered_map>
# include <memory>
# include <tuple>

# include "raylib.h"
# include "config/LoadedAssets.hpp"

# include "gui/rooms/VisualRoom.hpp"

# include "gui/entities/VisualEntity.hpp"
# include "gui/entities/VisualPlayer.hpp"
# include "gui/entities/User.hpp"

# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/Items/VisualItemKey.hpp"
# include "gui/Items/VisualItemConsumable.hpp"



class VisualWorldState
{
    private:
        std::unordered_map<std::string, std::unique_ptr<VisualRoom>>	rooms;
        std::unordered_map<std::string, std::unique_ptr<VisualEntity>>	entities;
        std::unordered_map<std::string, std::unique_ptr<VisualItem>>	items;
        std::unordered_map<std::string, std::unique_ptr<VisualPlayer>>	players;

        LoadedAssets													assets;
    public:
		std::unique_ptr<User>											user;

        VisualWorldState(
            const std::string &id,
			const Texture2D &texture,
			std::tuple<int, int> sprite_dim,
			float scale,
			const LoadedAssets &assets
		);
        ~VisualWorldState() = default;
        
        //===============================================================================
        //=============================== ITEM GETER ====================================
        //===============================================================================

        // Create and return untyped item, if the item was already created, simply return its pointer
        VisualItem*				getAddItem(const std::string &id, const Vector2 &creation_pos = Vector2{0.0, 0.0});
        // Create and return weapon item, if the item was already created, simply return its pointer
        VisualItemWeapon*		getAddWeapon(const std::string &id, const Vector2 &creation_pos = Vector2{0.0, 0.0});
        // Create and return key item, if the item was already created, simply return its pointer
        VisualItemKey*			getAddKey(const std::string &id, const Vector2 &creation_pos = Vector2{0.0, 0.0});
        // Create and return consumable item, if the item was already created, simply return its pointer
        VisualItemConsumable*	getAddConsumable(const std::string &id, const Vector2 &creation_pos = Vector2{0.0, 0.0});

        //===============================================================================
        //=============================== ROOM GETER ====================================
        //===============================================================================
        
        // Return room's pointer
        VisualRoom*             getRoom(const std::string &id);
};


