/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxInterface.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:10:22 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 13:44:32 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


TextBoxInterface::TextBoxInterface(
    const std::string &msg,
    int font_size
):
    msg(msg),
    FONT_SIZE(font_size)
{}

void                TextBoxInterface::displayText(float x, float y, Font font) {
    // DrawText(msg.c_str(), x, y, FONT_SIZE, WHITE);
    DrawTextEx(font, msg.c_str(), Vector2{x, y}, FONT_SIZE, 5, WHITE);
}

const std::string 	&TextBoxInterface::getMsg() const {
    return (this->msg);
}

bool				TextBoxInterface::isSkipped() const {
    return (this->skipped);
}
