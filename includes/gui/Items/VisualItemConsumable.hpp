/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemConsumable.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:37:07 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/13 16:15:51 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "raylib.h"
# include "gui/Items/VisualItem.hpp"

class VisualItemConsumable: public VisualItem
{
    public:
        VisualItemConsumable(const Item &item,
			const LoadedAssets &assets,
			float sprite_scale);

        ~VisualItemConsumable() = default;
};