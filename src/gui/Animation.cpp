/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:12:37 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/07 16:46:38 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gui/Animation.hpp"
# include "utils.h"

// ============================================================================
// ===========================   CONSTRUCTOR  =================================
// ============================================================================

Animation::Animation(
    const std::string& texture_path,
    std::tuple<float, float> frame_size,
    int frames_per_row,
    int frames_number,
    int first_frame,
    float speed
):
    _img(LoadTexture(texture_path.c_str())),
    _frame_size(frame_size),
    _frames_per_row(frames_per_row),
    _frames_number(frames_number),
    _first_frame(first_frame),
    _speed(speed)
    {
        if (this->_img.id == 0)
			this->sendObjectError("Error while loading texture");
        this->_curent_frame = this->_first_frame;
        this->_time_left = this->_speed;
    }

// ============================================================================
// ===========================   DESTRUCTOR   =================================
// ============================================================================

Animation::~Animation() {UnloadTexture(this->_img); }

// ============================================================================
// ===========================                =================================
// ============================================================================

void    Animation::update_frame()
{
    this->_time_left -= GetFrameTime();

    if (this->_time_left <= 0)
    {
        this->_time_left = this->_speed - this->_time_left;
        this->_curent_frame++;

        // If we reached our last frame
        if (this->_curent_frame >= this->_frames_number + this->_first_frame)
        {
            // we restart from the first frame
            this->_curent_frame = this->_first_frame;
        }
    }
}

Rectangle    Animation::get_frame()
{
    int x = (this->_curent_frame % this->_frames_per_row) * std::get<0>(this->_frame_size);
    int y = (this->_curent_frame / this->_frames_per_row) * std::get<0>(this->_frame_size);

    return ((Rectangle) {
        .x = (float)x,
        .y = (float)y,
        .width = std::get<0>(this->_frame_size),
        .height =  std::get<1>(this->_frame_size)
    });
}

void        Animation::draw_animation(float x, float y, float width = -1, float height = -1)
{
    if (width < 0)
        width = std::get<0>(this->_frame_size);
    if (height < 0)
        height = std::get<0>(this->_frame_size);

    Rectangle dest = Rectangle {
        .x = x,
        .y = y,
        .width = width,
        .height = height
    };

    DrawTexturePro(this->_img, this->get_frame(), dest, {0, 0}, 0.0f, WHITE);
    this->update_frame();
}

// Error
void Animation::sendObjectError(std::string error) {
   print_log(" ERROR: " + error + "\n");
}
