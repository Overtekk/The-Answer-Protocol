/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssetsUnloader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 14:04:20 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/12 14:27:25 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "config/LoadedAssets.hpp"

void UnloadAssets(LoadedAssets& assets) {
    for (auto loaded_sprites : assets.sprits) {
       UnloadTexture(loaded_sprites.second);
    }
    assets.sprits.clear();
}