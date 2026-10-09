/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 09:46:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:28:10 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "config/WorldConfig.hpp"


// - Debug -
void	debug_print_structure(WorldConfig& world, bool show_gui_info = false);
