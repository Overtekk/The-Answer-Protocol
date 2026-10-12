/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssetsLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:21:45 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/12 14:13:56 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "raylib.h"
# include "config/LoadedAssets.hpp"
# include "config/WorldConfig.hpp"
# include "gui.h"

bool LoadAssets(WorldConfig& config, LoadedAssets& assets) {
    for (auto unloaded_sprites : config.sprite) {
        assets.sprits.insert(
            {unloaded_sprites.first,
            LoadTexture(unloaded_sprites.second.path.c_str())}
        );
        if (assets.sprits[unloaded_sprites.first].id == 0) {
            UnloadAssets(assets);
            return (false);
        }
    }
    return (true);
}