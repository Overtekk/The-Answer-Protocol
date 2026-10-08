/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPTypes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:35:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 09:35:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum class SessionState   { CONNECTED, AUTHENTICATED, CLOSING };
enum class OperationState { SUCCESS, WOULD_BLOCK, PEER_CLOSED, FAILURE };
