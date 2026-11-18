/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssetsUnloader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 14:04:20 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/18 13:54:39 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "raytmx.h"
# include "config/LoadedAssets.hpp"

void UnloadAssets(LoadedAssets& assets) {
    for (auto loaded_sprites : assets.sprites) {
       UnloadTexture(loaded_sprites.second);
    }
    
    for (auto loaded_tiles_map : assets.assets.tile_maps) {
       UnloadTMX(loaded_tiles_map.second);
    }
    assets.sprites.clear();
    assets.tile_maps.clear();
}
