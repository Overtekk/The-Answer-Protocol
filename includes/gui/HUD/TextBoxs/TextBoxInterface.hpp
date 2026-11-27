/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxInterface.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:45:04 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 15:35:38 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "raylib.h"
# include <string>

// Interface class, not mean to be used, only its children's
class TextBoxInterface {
	protected:
		std::string	msg;

		bool		skipped = false;

		int			FONT_SIZE;

	public:
		TextBoxInterface(const std::string &msg, int font_size);
		virtual ~TextBoxInterface() = default;

		// Skip the box (set skipped attribut to true) according to the box type rule
		virtual void		skipTextBox() = 0;

		// Only draw text;
		virtual void		displayText(float x, float y, Font font);

		// Return the msg
		const std::string 	&getMsg() const;

		// Return if the box is skipped or not
		bool				isSkipped() const;
};