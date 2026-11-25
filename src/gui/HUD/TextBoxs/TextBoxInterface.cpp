/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxInterface.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:10:22 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 16:17:47 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


TextBoxInterface::TextBoxInterface(
    const std::string &msg
):
    msg(msg)
{}

void    TextBoxInterface::displayText() {
    DrawText(msg.c_str(), TEXT_X, TEXT_Y, 20, WHITE);
}