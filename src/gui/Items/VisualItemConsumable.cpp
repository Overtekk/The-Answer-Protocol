/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemConsumable.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:38:27 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/15 15:50:36 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include "raylib.h"
# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemConsumable.hpp"

VisualItemConsumable::VisualItemConsumable(
    const std::string &id,
	const LoadedAssets &assets,
	float sprite_scale
):
    VisualItem(id, assets, sprite_scale) {}
