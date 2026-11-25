/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WaitingTextBox.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:59:31 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 17:02:03 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/HUD/TextBoxs/WaitingTextBox.hpp"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


WaitingTextBox::WaitingTextBox(
    const std::string &msg
):  TextBoxInterface(msg)
{}

void	WaitingTextBox::skipTextBox() {
    if (IsKeyReleased(skip_key)) {
        skipped = true;
    }
}
