/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemConsumable.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:38:27 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/13 16:28:18 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemConsumable.hpp"

VisualItemConsumable::VisualItemConsumable(
    const Item &item,
	const LoadedAssets &assets,
	float sprite_scale
):
    VisualItem(item, assets, sprite_scale) {}
