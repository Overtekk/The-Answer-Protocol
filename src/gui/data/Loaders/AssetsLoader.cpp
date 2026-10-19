/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssetsLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:21:45 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/19 14:55:54 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "raylib.h"
# include "config/LoadedAssets.hpp"
# include "config/WorldConfig.hpp"
# include "gui.h"

bool LoadAssets(WorldConfig& config, LoadedAssets& assets) {
    // Load Sprites
    for (auto unloaded_sprites : config.sprite) {
        assets.sprites.insert(
            {unloaded_sprites.first,
            LoadTexture(unloaded_sprites.second.path.c_str())}
        );
        if (assets.sprites[unloaded_sprites.first].id == 0) {
            UnloadAssets(assets);
            return (false);
        }
    }

    // Load Tiles map
    for (auto unloaded_tile_map : config.locations) {
        assets.tile_maps.insert(
            {unloaded_tile_map.first,
            LoadTexture(unloaded_tile_map.second.tile_map.c_str())}
        );
        if (assets.tile_maps[unloaded_tile_map.first].id == 0) {
            UnloadAssets(assets);
            return (false);
        }
    }
    return (true);
}