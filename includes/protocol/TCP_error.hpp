/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_error.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:52:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 16:31:48 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

enum class TCPErrorCode {
	NAME_IN_USE,
	NO_EXIT,
	NOT_IN_GROUP,
	ALREADY_IN_GROUP,
	ITEM_NOT_FOUND,
	ITEM_NOT_IN_INVENTORY,
	NPC_NOT_FOUND,
	NPC_NOT_HOSTILE,
	NO_QUEST_AVAILABLE,
	CONNECTION_FAILED,
	SEND_FAILED,
	INVALID_USERNAME,
	SYSTEM_ERROR,
	CONNEXION_ERROR,
};


std::string getTCP_error(TCPErrorCode error_code, bool add_description = false);
std::string	getTCP_OK_operation(const std::string& msg);
