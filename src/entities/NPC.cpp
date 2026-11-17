/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/27 09:57:42 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/NPC.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
NPC::NPC(
    const std::string& id, const std::string& name, const std::string& description,
	EnemyType type, int health
):
	Entity(id, name, description, type, health) {}
