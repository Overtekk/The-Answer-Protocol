/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectsLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:25:21 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/15 16:41:23 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "config/WorldConfig.hpp"
# include "config/VisualWorldState.hpp"
# include "gui/Items/VisualItemWeapon.hpp"

void create_items(WorldConfig& config, VisualWorldState& data, const LoadedAssets &assets)
{
    for (auto items_config : config.items)
    {
        data.items.insert(
            {
                items_config.first,
                VisualItemWeapon(
                    items_config.first,
                    assets,
                    2.0f
                )
            }
        );
    }
}