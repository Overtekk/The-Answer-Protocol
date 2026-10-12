/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 12:16:02 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:48:13 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <iomanip>
# include <chrono>
# include <ctime>

# include "utils/colored_text.h"

# define TIME_FORMAT "%H:%M:%S"


void print_error(const std::string& error_msg) {
	std::cerr << RED << "[ERROR]: " << error_msg << RESET << "\n";
}

void print_success(const std::string& msg) {
	std::cout << GRN << msg << RESET << "\n";
}

void print_warning(const std::string& warning_msg) {
	std::cout << YEL << "[WARNING]: " << warning_msg << RESET << "\n";
}

void print_log(const std::string& log_msg) {
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm local_tm{};
	auto local_t = localtime_r(&time, &local_tm);
	if (local_t == nullptr) {
		std::cout << GRY << "[LOG] [" << "ERROR" << "]: " << log_msg << RESET << "\n";
		return;
	}
	std::cout << GRY << "[LOG] [" << std::put_time(&local_tm, TIME_FORMAT) << "]: " << log_msg << RESET << "\n";
}
