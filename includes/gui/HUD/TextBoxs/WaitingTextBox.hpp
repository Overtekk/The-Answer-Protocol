/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WaitingTextBox.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:46:49 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 15:36:38 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


class WaitingTextBox : public TextBoxInterface {
    protected:
        int skip_key = KEY_ENTER;

    public:
        WaitingTextBox(const std::string &msg, int font_size);

        // Skip the box when the player pressed the "Enter" key
        virtual void	skipTextBox() override;
};
