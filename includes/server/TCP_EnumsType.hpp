/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_EnumsType.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:33:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 10:33:20 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// === SERVER ONLY ===
enum class SessionState {CONNECTED, AUTHENTICATED};
enum class OperationState {SUCCESS, WAITING, DECONNEXION, ERROR, NETWORK_ERROR};
