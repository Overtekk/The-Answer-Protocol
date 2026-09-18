/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/18 15:40:30 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "base_class/entities/Player.hpp"
# include "base_class/items/Item.hpp"

int main() {
	std::cout << "Hello World, i'm the cli!";

	Player testPlayer("Test", "t", 20);
	Item testItem("Super Item", "t");

	return 0;
}
