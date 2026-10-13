/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/09 11:57:41 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/NPC.hpp"


// --- CONSTRUCTOR ---
NPC::NPC(
    const std::string& id, const std::string& name, const std::string& description,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	Entity(id, name, description, type, health),
	_dialogue(dialogue)
{}
