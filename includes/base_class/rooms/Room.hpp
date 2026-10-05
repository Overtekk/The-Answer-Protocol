/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:17 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/05 16:08:51 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <string>
# include <filesystem>
# include <unordered_map>
# include "base_class/items/Item.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "base_class/entities/PNJ.hpp"
// # include "base_class/entities/WorldConfig.hpp"

namespace fs = std::filesystem;

class Room {
    private :
        std::string                                     _name;
        std::string                                     _description;
        fs::path                                        _background;
        std::unordered_map<ItemID, Item*>               _items;
        std::unordered_map<std::string, Player*>        _players;
        std::unordered_map<std::string, PNJ*>           _pnj;
        // std::unordered_map<Direction, std::string>   _exits;
        bool                                            _save_point;
        bool                                            _special;

    public:
        // Constructor
        Room(const std::string& name, const std::string& description, const fs::path& background, 
        const bool _save_point, const bool _special);

        // Name
        std::string             getName() const;
        bool                    setName(const std::string& new_name);

        // Description
        std::string             getDesription() const;
        bool                    setDescription(const std::string& new_desc);

        // Players
        bool                    addPlayer(Player* player);
        Player*                 popPlayer(const std::string& name);
        Player*                 getPlayer(const std::string& name);

        // PNJ
        bool                    addPNJ(PNJ* pnj);
        PNJ*                    popPNJ(const std::string& name);
        PNJ*                    getPNJ(const std::string& name);

        // Items
        bool                    placeItem(Item* item);
        Item*                   popItem(ItemID item_id);
        Item*                   getItem(ItemID item_id);

        // Special stats
        bool                    isSavePoint() const;
        bool                    isSpecial() const;

        // Texture
        fs::path                getBGTexturePath() const;

        // Destructor
        virtual ~Room() = default;

        // Error
        std::string sendObjectError(std::string error) const;
};
