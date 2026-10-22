/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualWorldState.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:35:42 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/21 14:00:44 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <unordered_map>
# include <memory>
# include <tuple>

# include "raylib.h"
# include "config/WorldConfig.hpp"
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
        VisualItem*				getAddItem(const std::string &id);
        VisualItemWeapon*		getAddWeapon(const std::string &id);
        VisualItemKey*			getAddKey(const std::string &id);
        VisualItemConsumable*	getAddConsumable(const std::string &id);

        //===============================================================================
        //=============================== ROOM GETER ====================================
        //===============================================================================
        
        VisualRoom*             getRoom(const std::string &id);
};


