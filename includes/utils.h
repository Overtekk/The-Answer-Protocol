/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:14:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:29:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <queue>

# include "config/WorldConfig.hpp"
# include "config/Enums.hpp"

# define pass (void)0


// - Print -
void	print_error(const std::string& error_msg);
void	print_success(const std::string& msg);
void	print_warning(const std::string& warning_msg);
void	print_log(const std::string& log_msg);

// - Enum convert -
std::string	direction_to_string(Direction dir);
std::string	enemy_type_to_string(EnemyType type);
std::string	item_type_to_string(ItemType type);

// Extract a element from a queue, pop it and return the value
template <typename T>
T pop_front(std::queue<T>& q) {
    T val = std::move(q.front());
    q.pop();
    return val;
}
