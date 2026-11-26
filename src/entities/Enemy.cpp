/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:11:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/26 11:08:56 by roandrie         ###   ########.fr       */
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

bool	Enemy::getCanBeSparedState() { return _can_be_spared; }

bool	Enemy::hasBeenAttacked() { return _have_been_attacked; }

bool	Enemy::hasBeenSpared() { return _have_been_spared; }

void	Enemy::setCanBeSparedState(bool new_state) { _can_be_spared = new_state; }

void	Enemy::changeAttackedState(bool new_state) { _have_been_attacked = new_state; }

void	Enemy::changeSparedState(bool new_state) { _have_been_spared = new_state; }
