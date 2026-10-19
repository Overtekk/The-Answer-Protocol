/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectsLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:25:21 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/19 09:20:12 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <memory>
# include <tuple>
# include "config/WorldConfig.hpp"
# include "config/VisualWorldState.hpp"
# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/Items/VisualItemKey.hpp"
# include "gui/Items/VisualItemConsumable.hpp"
# include "config/Enums.hpp"
# include "utils.h"


// void    create_items(WorldConfig& config, VisualWorldState& data, const LoadedAssets &assets)
// {
//     std::unique_ptr<VisualItem> item;
    
//     for (auto items_config : config.items) {
//         switch (items_config.second.type) {
//             case ItemType::WEAPON :
//                 item = std::make_unique<VisualItemWeapon>(items_config.first, assets, 2.0f);
//                 break;
//             case ItemType::KEY :
//                 item = std::make_unique<VisualItemKey>(items_config.first, assets, 2.0f);
//                 break;
//             case ItemType::CONSUMABLE :
//                 item = std::make_unique<VisualItemConsumable>(items_config.first, assets, 2.0f);
//                 break;
//             default:
//                 item = std::make_unique<VisualItem>(items_config.first, assets, 2.0f);
//         }
//         auto [it, boolean] = data.items.emplace(
//                 items_config.first,
//                 std::move(item)
//         );
//         item.reset();
        
        
//         if (boolean == false)
//         {
//             print_warning("Can't add item " + items_config.first + " skipping");
//         }
//     }
// }

bool    LoadData(WorldConfig& config, VisualWorldState& data, const LoadedAssets &assets)
{
    data.user = std::make_unique<User>("Kris", assets.sprits.at("player"), std::make_tuple(19, 38), 2.0f);
    
    std::ignore = config;
    
    std::cout << "Printing data\n";
    return (true);
}
