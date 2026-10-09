/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/09 11:57:47 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/NPCShop.hpp"


// --- CONSTRUCTOR ---
NPCShop::NPCShop(
    const std::string& id, const std::string& name, const std::string& description,
	std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
):
	NPC(id, name, description, dialogue, type, health) {}
