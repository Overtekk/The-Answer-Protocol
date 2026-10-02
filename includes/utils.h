/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:14:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/02 15:15:51 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

void print_error(const std::string& error_msg);
void print_success(const std::string& msg);
void print_warning(const std::string& warning_msg);
void print_log(const std::string& log_msg);
