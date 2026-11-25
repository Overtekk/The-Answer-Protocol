/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WaitingTextBox.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:46:49 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 16:58:21 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "raylib.h"
# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


class WaitingTextBox : public TextBoxInterface {
    protected:
        int skip_key = KEY_ENTER;

        WaitingTextBox(const std::string &msg);

        virtual void	skipTextBox() override;
};
