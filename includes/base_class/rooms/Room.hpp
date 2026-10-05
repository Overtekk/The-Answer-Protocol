/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:17 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/05 13:56:32 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <string>
# include <filesystem>
# include <map>
# include <unordered_map>
# include "base_class/items/Item.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
// # include "base_class/entities/WorldConfig.hpp"

namespace fs = std::filesystem;

class Room {
    private :
        std::string                                     _name;
        std::string                                     _description;
        fs::path                                        _background;
        std::map<ItemID, std::unique_ptr<Item>>         _items;
        std::map<std::string, Player*>                  _players;
        std::map<std::string, Entity*>                  _pnj;
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
        Player*                 getplayer(const std::string& name);

        // PNJ
        // bool                    addPlayer(Player* player);
        // Player*                 popPlayer(const std::string& name);
        // Player*                 getplayer(const std::string& name);

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
