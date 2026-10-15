/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemKey.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:38:44 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/13 16:13:45 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemKey.hpp"


VisualItemKey::VisualItemKey(
    const Item &item,
	const LoadedAssets &assets,
	float sprite_scale
):
    VisualItem(item, assets, sprite_scale) {}