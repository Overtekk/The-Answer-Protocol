/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 13:31:18 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "config/Enums.hpp"


// * ABSTRACT CLASS *
class Entity {
	private :
		std::string	_id;
		std::string	_description;
		int			_health;
		int			_max_health;
		EnemyType	_type;
		int			_attack = 1;

		bool		_in_combat = false;

	protected :
		std::string	_name;

	public :
		// --- CONSTRUCTOR ---
		Entity(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health);
		// --- DESTRUCTOR ---
		virtual ~Entity() = default;

		// --- GETTER ---
		const std::string&	getID() const;
		const std::string&	getName() const;
		int 				getHealth() const;
		int					getMaxHealth() const;
		virtual EnemyType	getType() const;
		bool				inCombat();
		int					getAttackValue() const;

		// --- SETTER ---
		void	setHealth(int new_value);
		void	setCombat(bool new_state);
		void	setAttackValue(int new_value);

		// --- ERROR ---
		void sendObjectError(const std::string& error) const;
};
