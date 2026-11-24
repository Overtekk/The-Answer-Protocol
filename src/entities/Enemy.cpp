/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:11:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/18 11:35:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/Enemy.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
Enemy::Enemy(
    const std::string& id, const std::string& name, const std::string& description,
	EnemyType type, int health
):
	Entity(id, name, description, type, health) {}

// ============================================================================
// =====================         METHODS      =================================
// ============================================================================

bool	Enemy::getSparedState() { return _can_be_spared; }

void	Enemy::setSparedState(bool new_state) { _can_be_spared = new_state; }
