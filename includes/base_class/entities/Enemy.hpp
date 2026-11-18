/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:10:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/18 11:58:13 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "Entity.hpp"
# include "config/Enums.hpp"


// * REPRESENT AN ENEMY *
class Enemy : public Entity {
	private:

		bool	_can_be_spared = false;

	public :
		// --- CONSTRUCTOR ---
		Enemy(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health
		);
		// --- DESTRUCTOR ---
		~Enemy() override = default;

		bool	getSparedState();
		void	setSparedState(bool new_state);
};
