/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/27 09:55:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "Entity.hpp"
# include "config/Enums.hpp"


// * Represent a NPC *
class NPC : public Entity {
	public :
		// --- CONSTRUCTOR ---
		NPC(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health
		);
		// --- DESTRUCTOR ---
		~NPC() override = default;
};
