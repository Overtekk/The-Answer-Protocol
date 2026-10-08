/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:43:33 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 15:54:06 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server/TCPSession.hpp"

#pragma once

void	print_log_message(TCPSession& session, const std::string& log_msg);
