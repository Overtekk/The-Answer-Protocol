/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WaitingTextBox.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:59:31 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 13:42:31 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/HUD/TextBoxs/WaitingTextBox.hpp"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


WaitingTextBox::WaitingTextBox(
    const std::string &msg,
    int font_size
):  TextBoxInterface(msg, font_size)
{}

void	WaitingTextBox::skipTextBox() {
    if (IsKeyReleased(skip_key)) {
        skipped = true;
    }
}
