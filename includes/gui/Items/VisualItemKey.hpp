/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemKey.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:36:35 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/15 15:48:48 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include "raylib.h"
# include "gui/Items/VisualItem.hpp"

class VisualItemKey: public VisualItem
{
    public:
        VisualItemKey(
            const std::string &id,
			const LoadedAssets &assets,
			float sprite_scale);

        ~VisualItemKey() = default;
};
