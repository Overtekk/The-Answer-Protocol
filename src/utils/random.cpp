/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:02:34 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/20 14:20:21 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <random>

# include "utils.h"
# include "config/config_messages.h"


// Give a random number between int min and int max
int	generate_value_random_between(int min, int max) {
	if (min >= max) {
		print_log(errRandomGenerationBounds(min, max));
		return -1;
	}

	static std::mt19937 gen(std::random_device{}());

	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

