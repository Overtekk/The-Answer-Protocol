/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameCamera.cpp.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 13:37:15 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/23 15:52:13 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"

# include "gui/entities/User.hpp"
# include "gui/GameCamera.hpp"
# include "gui/rooms/VisualRoom.hpp"
# include "gui.h"

GameCamera::GameCamera(
    User *user,
	const Vector2 &target,
	float zoom,
	const Vector2 &offset,
	float rotation
):
    _user(user),
	// offsets for clamping
	_offset_width(GetRenderWidth()/4.0f),
	_offset_height(GetRenderHeight()/4.0f)
{
    _camera.target = target;
    _camera.offset = offset;
    _camera.rotation = rotation;
    _camera.zoom = zoom;
}


void GameCamera::update(VisualRoom *actual_room) {
    this->_camera.target = clamp(this->_user->getPos(),
		actual_room->getWidth() - this->_offset_width,
		this->_offset_width,
		actual_room->getHeight() - _offset_height,
		_offset_height
	);
}


Camera2D	*GameCamera::getCamera() {
	return (&this->_camera);
}
