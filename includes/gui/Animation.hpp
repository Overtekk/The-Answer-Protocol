/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animation.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 14:12:05 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/08 14:54:50 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <tuple>
# include "raylib.h"

class Animation
{
    private:
        Texture2D                   _img;
        std::tuple<float, float>    _frame_size; // width, height
        
        int                         _frames_per_row;
        int                         _frames_number;
                                    // it doesn't alaways start at 0, depend if an img containe different animation
        int                         _first_frame; 
        int                         _curent_frame;
        
        float                       _speed;
        float                       _time_left;
    public:
        Animation(const std::string& texture_path,
                std::tuple<float, float> frame_size,
                int frames_per_row,
                int frames_number,
                int first_frame,
                float speed);
        // destructor
        ~Animation();

        // Protection against copying texture
		Animation(const Animation&) = delete;
		Animation& operator=(const Animation&) = delete;

        // update _curent_frame attribut 
        void            update_frame();
        // return the _curent_frame rectangle
        Rectangle       get_frame();
        // play animation and update _curent_frame
        void            play_animation(float x, float y, float scale = 1.0f, bool flip = false, float width = -1.0f, float height = -1.0f);
        // draw curent frame
        void            draw_curent_frame(float x, float y, float scale = 1.0f, bool flip = false, float width = -1.0f, float height = -1.0f);

        // set the curent frame to the first frame
        void            reset();

        // reset the time_left befor switching frame
        void            reset_time_left();

        // manually set the curent frame (2 mean the third frame cause we start from 0)
        void            set_frame(int frame);

        // Error
        void            sendObjectError(std::string error);
};
