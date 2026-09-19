/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/19 10:47:02 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <memory>
# include "base_class/entities/Player.hpp"
# include "base_class/items/Item.hpp"
# include "base_class/items/Weapon.hpp"

int main() {
	std::cout << "Hello World, i'm the cli!\n";

	Player test_player("Player Test", "t", 20);
	auto wooden_sword = std::make_unique<Weapon>("Wooden Sword", "t");
	auto excalibur = std::make_unique<Weapon>("Excalibur", "t");

	test_player.addItemToInventory(std::move(wooden_sword));
	test_player.addItemToInventory(std::move(excalibur));
	std::cout << test_player.getItemInInventory() << "\n";

	if (test_player.removeItemToInventory(wooden_sword->getName()))
		std::cout << "Removed " << wooden_sword->getName() << " from inventory.\n";

	std::cout << test_player.getItemInInventory();

	return 0;
}
