/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnemyTemplate.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:21:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/10 10:08:32 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Template for enemies/boss with specific battles interactions/mini-games

#pragma once

# include <string>
# include <unordered_map>

# include "Enums.hpp"


struct EnemyTemplate {
	EnemyBehavior	behavior;
	int				attack;
	std::unordered_map<std::string, std::string>	dialogue;
};

// * Return the template of the enemy/boss with this ID (the YAML key, lowercase), or nullptr if there is none. *
const EnemyTemplate*	find_enemy_template(const std::string& entity_id);
