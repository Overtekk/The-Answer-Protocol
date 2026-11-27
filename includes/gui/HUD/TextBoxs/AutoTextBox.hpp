/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoTextBox.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:45:52 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 15:36:06 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


class AutoTextBox : public TextBoxInterface {
    protected:
        float skip_timer;
        float delta = 0.0f;

    public:
        AutoTextBox(const std::string &msg, int font_size , float skip_time = 2.0);

        // Skip the box when the timer ended (default = 2.0s)
        virtual void	skipTextBox() override;
};