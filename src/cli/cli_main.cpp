/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 10:42:28 by roandrie         ###   ########.fr       */
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

	ItemID sword_id = wooden_sword->getId();
	// ItemID excalibur_id = excalibur->getId();

	test_player.addItemToInventory(std::move(wooden_sword));
	test_player.addItemToInventory(std::move(excalibur));

	std::cout << test_player.getItemInInventory() << "\n";

	if (test_player.removeItemFromInventory(sword_id)) {
        std::cout << "Removed item from inventory.\n";
        wooden_sword = nullptr;
    }

	std::cout << test_player.getItemInInventory();

	return 0;
}
