/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/27 09:58:03 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/NPCShop.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
NPCShop::NPCShop(
    const std::string& id, const std::string& name, const std::string& description,
	EnemyType type, int health
):
	NPC(id, name, description, type, health) {}
