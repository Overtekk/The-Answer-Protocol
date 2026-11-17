/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:11:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/27 09:57:15 by roandrie         ###   ########.fr       */
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
