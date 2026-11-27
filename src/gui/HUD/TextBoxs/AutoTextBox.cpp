/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoTextBox.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:32:47 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 13:42:12 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raylib.h"
# include "gui/HUD/TextBoxs/AutoTextBox.hpp"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


AutoTextBox::AutoTextBox(
    const std::string &msg,
    int font_size,
    float skip_time
):  TextBoxInterface(msg, font_size),
    skip_timer(skip_time)
{}

void	AutoTextBox::skipTextBox() {
    delta += GetFrameTime();

    if (delta >= 1.0f){
        delta = 0.0f + (delta - 1.0f);
        skip_timer -= 1.0f;
    }

    if (skip_timer <= 0.0) {skipped = true; }
}
