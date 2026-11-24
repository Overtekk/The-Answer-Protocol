/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadedAssets.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:23:31 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/18 12:37:16 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unordered_map>
# include <string>
# include "raylib.h"
# include "raytmx.h"


struct Assets
{
    std::unordered_map<std::string, Texture2D> sprites;
    std::unordered_map<std::string, TmxMap*> tile_maps;
};


struct LoadedAssets
{
    Assets                                      assets;
    
    std::unordered_map<std::string, Texture2D> sprites;
    std::unordered_map<std::string, TmxMap*> tile_maps;
};
