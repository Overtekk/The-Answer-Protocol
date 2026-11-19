/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:14:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/18 11:43:48 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/entities/Boss.hpp"
# include "base_class/entities/Enemy.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
Boss::Boss(
    const std::string& id, const std::string& name, const std::string& description,
	EnemyType type, int health
):
	Enemy(id, name, description, type, health) {}
