/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:13:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/27 09:54:52 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "Entity.hpp"
# include "config/Enums.hpp"


// * Represent a boss enemy *
class Boss : public Entity {
	public :
		// --- CONSTRUCTOR ---
		Boss(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health
		);
		// --- DESTRUCTOR ---
		~Boss() override = default;
};
