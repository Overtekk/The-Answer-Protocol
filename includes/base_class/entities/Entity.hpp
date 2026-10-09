/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 11:55:06 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

# include "config/Enums.hpp"


// * ABSTRACT CLASS *
class Entity {
	private :
		std::string	_id;
		std::string	_description;
		int 		_health;
		EnemyType	_type;

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
		virtual EnemyType	getType() const;

		// --- SETTER ---
		void				setHealth(int new_value);

		// --- ERROR ---
		void sendObjectError(const std::string& error) const;
};
