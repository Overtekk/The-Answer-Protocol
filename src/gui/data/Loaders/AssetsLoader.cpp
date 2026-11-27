/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssetsLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:21:45 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 15:19:22 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <iostream>
# include <string>

# include "raylib.h"
# include "raytmx.h"
# include "config/LoadedAssets.hpp"
# include "config/WorldConfig.hpp"
# include "gui.h"


TmxMap  *LoadTile(LoadedAssets& assets, const std::string &path) {
    // if assets not already loaded
    if (assets.assets.tile_maps.find(path) == assets.assets.tile_maps.end()){
        assets.assets.tile_maps.emplace(path, LoadTMX(path.c_str()));
        std::cout << "LOADED [" << path << "]\n";
    }
    return (assets.assets.tile_maps.at(path));
}

Texture2D  &LoadSprite(LoadedAssets& assets, const std::string &path) {
    // if assets not already loaded
    if (assets.assets.sprites.find(path) == assets.assets.sprites.end()){
        assets.assets.sprites.emplace(path, LoadTexture(path.c_str()));
        std::cout << "LOADED [" << path << "]\n";
    }
    return (assets.assets.sprites.at(path));
}

bool LoadAssets(WorldConfig& config, LoadedAssets& assets) {
    std::cout << "\n";

    // Load Sprites
    for (const auto &[name, sprite] : config.sprite) {
        assets.sprites.insert(
            {name,
            LoadSprite(assets, sprite.path)}
        );
        if (assets.sprites[name].id == 0) {
            UnloadAssets(assets);
            return (false);
        }
    }

    // Load Tiles map
    for (const auto &[name, loc] : config.locations) {
        assets.tile_maps.insert(
            {name,
            LoadTile(assets, loc.tile_map)}
        );
        if (assets.tile_maps[name] == nullptr) {
            UnloadAssets(assets);
            return (false);
        }
    }

    // Load Font
    assets.font = LoadFont("assets/font/undertale-deltarune-extended-fixed.otf");
    if (IsFontValid(assets.font) == false) {
        UnloadAssets(assets);
        return (false);
    }

    std::cout << "\n";
    return (true);
}
