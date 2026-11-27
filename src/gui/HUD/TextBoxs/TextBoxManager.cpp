/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:22:38 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 13:45:26 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
# include <string>
# include <vector>
# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"
# include "gui/HUD/TextBoxs/TextBoxManager.hpp"


void	TextBoxManager::loadAssets(LoadedAssets &assets){
    this->_hud_texture = assets.sprites.at("HUD");
    this->_font = assets.font;
}

std::vector<std::string>	TextBoxManager::msg_splitter(std::string &msg) {
    size_t last_index = 0;
    std::vector<std::string> result;
    std::string line = "";

    for (size_t i = 0 ; i < msg.length(); i++) {
        line = msg.substr(last_index, (i - last_index) + 1);
        // split if \n
        if (line.back() == '\n') {
            result.push_back(line);
            i++;
            last_index = i;
        }
        // if line too long, split from the last space 
        else if (MeasureTextEx(_font, line.c_str(), FONT_SIZE, 5).x > max_txt_lenght) {
            size_t last_space_index = line.rfind(" ");
            result.push_back(line.substr(0, last_space_index) + "\n");
            i = last_index + last_space_index + 1;
            last_index = i;
        }
    }
    result.push_back(line);
    return (result);
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
        this->_boxes.front().get()->displayText(rec_dest.x - x_txt_offset, rec_dest.y - y_txt_offset, _font);
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