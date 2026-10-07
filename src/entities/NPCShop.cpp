/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/07 11:59:54 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/NPCShop.hpp"

// --- CONSTRUCTOR ---
NPCShop::NPCShop(
    const std::string& name, const std::string& description,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	NPC(name, description, dialogue, type, health) {}
