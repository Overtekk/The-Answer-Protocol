/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/06 11:50:39 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/NPCShop.hpp"

// --- CONSTRUCTOR ---
NPCShop::NPCShop(
    const std::string& name, const std::string& description, const fs::path& sprite,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	NPC(name, description, sprite, dialogue, type, health) {}
