/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemConsumable.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:37:07 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/15 15:50:09 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include "raylib.h"
# include "gui/Items/VisualItem.hpp"

class VisualItemConsumable: public VisualItem
{
    public:
        VisualItemConsumable(
            const std::string &id,
			const LoadedAssets &assets,
			float sprite_scale);

        ~VisualItemConsumable() = default;
};