/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PNJ.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/05 14:07:28 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/PNJ.hpp"

PNJ::PNJ(
    const std::string& name, const fs::path& sprite, int health
): Entity(name, sprite, health) {}
