/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadedAssets.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 13:23:31 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/12 14:27:52 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <unordered_map>
# include <string>
# include "raylib.h"


struct LoadedAssets
{
    std::unordered_map<std::string, Texture2D> sprits;
};
