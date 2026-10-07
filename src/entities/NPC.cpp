/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/07 11:59:07 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/NPC.hpp"

// --- CONSTRUCTOR ---
NPC::NPC(
    const std::string& name, const std::string& description,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	Entity(name, description, type, health),
	_dialogue(dialogue)
{}
