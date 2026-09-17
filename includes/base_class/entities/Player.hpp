/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/17 16:07:48 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Entity.hpp"

class Player : public Entity {
	public:
		Player(const std::string& name, int health) :
			Entity(name, health) {}
};
