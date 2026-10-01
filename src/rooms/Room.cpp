/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:13 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/01 16:28:10 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/rooms/Room.hpp"

Room::Room(
    const std::string& name, const std::string& description, const fs::path& background,
    const bool save_point, const bool special
):
    _name(name),
    _description(description),
    _background(background),
    _save_point(save_point),
    _special(special)
    {
    }

std::string Room::getName() const {
    return (this->_name);
}

bool        Room::isSavePoint() const {
    return (this->_save_point);
}

bool        Room::isSpecial() const {
    return (this->_special);
}
