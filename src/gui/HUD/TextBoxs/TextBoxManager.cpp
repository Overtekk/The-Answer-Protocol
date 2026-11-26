/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:22:38 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/26 16:12:56 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"
# include "gui/HUD/TextBoxs/TextBoxManager.hpp"


void	TextBoxManager::loadAssets(LoadedAssets &assets){
    this->_hud_texture = assets.sprites.at("HUD");
}


void    TextBoxManager::updatedTextBoxes() {
    if (this->_boxes.empty() == false){
        // update box life time
        this->_boxes.front().get()->skipTextBox();

        // if the box's life time as ended, remove it
        if (this->_boxes.front().get()->isSkipped() == true) {
            this->_boxes.pop();
        }
    }
}

bool	TextBoxManager::boxQueuEmpty() const {
    return (this->_boxes.empty());
}

void    TextBoxManager::drawTextBoxes() {
    if (this->_boxes.empty() == false) {
		
        DrawTexturePro(_hud_texture, rec_src, rec_dest, Vector2{rec_dest.width / 2, rec_dest.height / 2}, 0.0f, WHITE);
        this->_boxes.front().get()->displayText(rec_dest.x - x_txt_offset, rec_dest.y - y_txt_offset, max_txt_lenght);
    }
}

//        This is for handling any type of TextBox.
//                          |
//                          |
//                          V
// template <typename text_box_type, typename... Args_type>  <---- This one is for taking any type of parameter to pass to the TextBox class constructor.


//			Here, we take a variable number of parameters, each of a different type (defined by Args_type). && is the universal reference; it accepts any type of value (rvalue, lvalue).
//												|
//												|
//												V
// void    TextBoxManager::addTextBox(Args_type&&... args) {


//								set the TextBox type		A special function that unpacks the arguments and associates them with the types passed to `Args_type` (it also handles both rvalues ​​and lvalues).
//												|				|
//												V				V
//     this->_boxes.push(std::make_unique<text_box_type>(std::forward<Args_type>(args)...));
//																						^
//																						|
//																						|
//																						This is for unpacking

// }