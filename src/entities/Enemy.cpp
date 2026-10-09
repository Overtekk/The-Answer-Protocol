/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:11:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 11:57:28 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/Enemy.hpp"


// --- CONSTRUCTOR ---
Enemy::Enemy(
    const std::string& id, const std::string& name, const std::string& description,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	Entity(id, name, description, type, health),
	_dialogue(dialogue)
{}
