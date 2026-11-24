/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCamera.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 13:36:40 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/24 09:56:40 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "raylib.h"

# include "gui/entities/User.hpp"
# include "gui/rooms/VisualRoom.hpp"


class GameCamera
{
    private:
		Camera2D	_camera;
		User		*_user;

		float		_offset_width;
		float		_offset_height;

    public:
	GameCamera(
		User *user,
		const Vector2 &target,
		float zoom = 1.0,
		const Vector2 &offset = Vector2{GetRenderWidth()/2.0f, GetRenderHeight()/2.0f},
		float rotation = 0.0
	);

	// Update the camera target (camera target the player), actual_room is
	// needed to clamp camera position
	void update(VisualRoom *actual_room);

	// Return a camera pointer
	Camera2D	*getCamera();

	~GameCamera() = default;

};
