/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:13:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 11:55:09 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>
# include "Entity.hpp"
# include "config/Enums.hpp"

// * Represent a boss enemy *
class Boss : public Entity {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // --- CONSTRUCTOR ---
        Boss(
			const std::string& name, const std::string& description, std::unordered_map<std::string,
      std::string> dialogue, EnemyType type, int health
		);
        // --- DESTRUCTOR ---
        ~Boss() = default;
};
