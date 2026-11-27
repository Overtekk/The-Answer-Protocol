/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:21:42 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 15:30:22 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <queue>
# include <memory>
# include <string>
# include <vector>
# include "raylib.h"
# include "config/LoadedAssets.hpp"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"

// Singleton class
class TextBoxManager {
    private:
		Texture2D	                    					_hud_texture;
		Font												_font;
        std::queue<std::unique_ptr<TextBoxInterface>>    	_boxes;
        
		Rectangle						rec_src{6.0f, 552.0f, 593.0f, 167.0f};
		Rectangle						rec_dest{
			float(GetScreenWidth()) / 2.0f,
			float(GetScreenHeight()) - rec_src.height / 2.0f,
			rec_src.width,
			rec_src.height
		};

		float	x_txt_offset = rec_dest.width / 2.0f - 30;
		float	y_txt_offset = rec_dest.height / 2.0f - 20;
		float	max_txt_lenght = rec_dest.width - 30 * 2;
		int		FONT_SIZE = 40;

        TextBoxManager() {} // private constructor to bloc external instantiation
        
        TextBoxManager(const TextBoxManager &textb) = delete; // copy constructor removed to avoid external copy
        TextBoxManager& operator=(const TextBoxManager &textb) = delete; // "=" opperator removed to guess what.... avoid external copy

		// format text (add \n when the line is too long) and split every lines
		std::vector<std::string>	msg_splitter(std::string &msg);
    
    public:
	
		// access the unique instance
		static TextBoxManager &access() {
			static TextBoxManager text_box;
			return (text_box);
		}
		
		// Load box assets
		void	loadAssets(LoadedAssets &assets);

		template <typename text_box_type, typename... Args_type>
		// Automatically add boxes of a given type, if the text is too long, another TextBox will be added
		// Accepts all arguments for the various boxes
		void    addTextBox(std::string &&msg, Args_type&&... args) {
			std::vector<std::string>	mini_msgs = msg_splitter(msg);
			std::string					new_msg = "";
			int							count = 0;
			
			for (std::string mini_msg : mini_msgs) {
				new_msg += mini_msg;
				count++;
				if (count >= 3 or mini_msgs.back() == mini_msg) {
					this->_boxes.push(std::make_unique<text_box_type>(new_msg, FONT_SIZE, std::forward<Args_type>(args)...));
					new_msg = "";
					count = 0;
				}
			}
		}

		// update box lifetime and remove it when the fifetime as eddend
        void    updatedTextBoxes();

		// Return is the queu is empty or not
		bool	boxQueuEmpty() const;

		// Draw the box and display the formated text
        void    drawTextBoxes();
};
