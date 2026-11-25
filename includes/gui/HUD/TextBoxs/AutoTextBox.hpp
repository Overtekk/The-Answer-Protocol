/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoTextBox.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:45:52 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 16:52:45 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "gui/HUD/TextBoxs/TextBoxInterface.hpp"


class AutoTextBox : public TextBoxInterface {
    protected:
        float skip_timer;
        float delta = 0.0f;

        AutoTextBox(const std::string &msg, float skip_time = 2.0);

        virtual void	skipTextBox() override;
};