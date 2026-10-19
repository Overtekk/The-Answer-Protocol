/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualItemWeapon.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:36:16 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/19 10:54:03 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include "raylib.h"
# include "gui/Items/VisualItem.hpp"

class VisualItemWeapon: public VisualItem
{
    private:
        Texture2D				    _obj_texture;
		const int					_OBJ_WIDTH = 13.0f;
		const int					_OBJ_HEIGHT = 18.0f;
    public:
        VisualItemWeapon(
            const std::string &id,
			const LoadedAssets &assets,
			float sprite_scale);

        ~VisualItemWeapon() = default;

        // Draw item, if width and height are not specified, it will use original sprite width height
		void DrawWeaponIcon(float x, float y, float width = -1, float height = -1);
};

