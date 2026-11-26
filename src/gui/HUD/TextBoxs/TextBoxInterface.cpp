/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxInterface.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:10:22 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/26 16:23:00 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "iostream"
# include <string>
# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


TextBoxInterface::TextBoxInterface(
    const std::string &msg
):
    msg(msg)
{}

void                TextBoxInterface::displayText(float x, float y, float max_line_lenght) {
    int lenght = MeasureText(msg.c_str(), FONT_SIZE);
    if (lenght > max_line_lenght) {
        std::cout << "Too big\n";
    }
    DrawText(msg.c_str(), x, y, FONT_SIZE, WHITE);
}

const std::string 	&TextBoxInterface::getMsg() const {
    return (this->msg);
}

bool				TextBoxInterface::isSkipped() const {
    return (this->skipped);
}
