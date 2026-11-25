/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxInterface.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:45:04 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 16:38:48 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>

class TextBoxInterface {
	protected:
		std::string	msg;

		bool		skipped = false;
		float		TEXT_X = 400;
		float		TEXT_Y = 50;
	
		TextBoxInterface(const std::string &msg);

		virtual void	skipTextBox() = 0;
		
		// only draw text;
		virtual void	displayText();
};