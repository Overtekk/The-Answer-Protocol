/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:21:42 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/26 16:46:43 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <queue>
# include <memory>
# include <utility>
# include "raylib.h"
# include "config/LoadedAssets.hpp"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"

// Singleton class
class TextBoxManager {
    private:
		Texture2D	                    					_hud_texture;
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

        TextBoxManager() {} // private constructor to bloc external instantiation
        
        TextBoxManager(const TextBoxManager &textb) = delete; // copy constructor removed to avoid external copy
        TextBoxManager& operator=(const TextBoxManager &textb) = delete; // "=" opperator removed to guess what.... avoid external copy
    
    public:
	
		// access the unique instance
		static TextBoxManager &access() {
			static TextBoxManager text_box;
			return (text_box);
		}
		
		// Load box assets
		void	loadAssets(LoadedAssets &assets);

		template <typename text_box_type, typename... Args_type>
		void    addTextBox(Args_type&&... args) {
			std::unique_ptr<text_box_type> new_text_box = std::make_unique<text_box_type>(std::forward<Args_type>(args)...);

			this->_boxes.push(std::move(new_text_box));
    		// this->_boxes.push(std::make_unique<text_box_type>(std::forward<Args_type>(args)...));
		}

        void    updatedTextBoxes();

		bool	boxQueuEmpty() const;

        void    drawTextBoxes();
};
