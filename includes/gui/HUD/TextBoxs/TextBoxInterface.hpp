/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxInterface.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:45:04 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/26 16:13:37 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>

class TextBoxInterface {
	protected:
		std::string	msg;

		bool		skipped = false;

		int			FONT_SIZE = 20;

	public:
		TextBoxInterface(const std::string &msg);
		virtual ~TextBoxInterface() = default;

		virtual void		skipTextBox() = 0;

		// only draw text;
		virtual void		displayText(float x, float y, float max_line_lenght);

		const std::string 	&getMsg() const;

		bool				isSkipped() const;
};