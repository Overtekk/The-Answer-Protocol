/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssetsLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:21:45 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/19 08:53:32 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <iostream>
# include <string>

# include "raylib.h"
# include "raytmx.h"
# include "config/LoadedAssets.hpp"
# include "config/WorldConfig.hpp"
# include "gui.h"
#include "utils.h"


TmxMap  *LoadTile(LoadedAssets& assets, const std::string &path) {
    try {
        return (assets.assets.tile_maps.at(path));
    }
    catch(...) {
        assets.assets.tile_maps.emplace(path, LoadTMX(path.c_str()));
        std::cout << "LOADED [" << path << "]\n";
        return (assets.assets.tile_maps.at(path));
    }
}

Texture2D  &LoadSprite(LoadedAssets& assets, const std::string &path) {
    try {
        return (assets.assets.sprites.at(path));
    }
    catch(...) {
        assets.assets.sprites.emplace(path, LoadTexture(path.c_str()));
        std::cout << "LOADED [" << path << "]\n";
        return (assets.assets.sprites.at(path));
    }
}

bool LoadAssets(WorldConfig& config, LoadedAssets& assets) {
    std::cout << "\n";

    // Load Sprites
    for (auto unloaded_sprites : config.sprite) {
        assets.sprites.insert(
            {unloaded_sprites.first,
            LoadSprite(assets, unloaded_sprites.second.path)}
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
            LoadTile(assets, unloaded_tile_map.second.tile_map)}
        );
        if (assets.tile_maps[unloaded_tile_map.first] == nullptr) {
            UnloadAssets(assets);
            return (false);
        }
    }
    std::cout << "\n";
    return (true);
}
