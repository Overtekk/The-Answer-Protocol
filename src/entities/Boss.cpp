/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:14:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 11:50:01 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/Boss.hpp"

// --- CONSTRUCTOR ---
Boss::Boss(
    const std::string& name, const std::string& description, const fs::path& sprite,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	Entity(name, description, sprite, type, health),
	_dialogue(dialogue)
{}
