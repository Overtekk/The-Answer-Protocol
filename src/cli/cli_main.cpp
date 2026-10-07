/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:14:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 11:01:25 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <memory>
# include "base_class/entities/Player.hpp"
# include "base_class/items/Item.hpp"
# include "base_class/items/ItemWeapon.hpp"

int main() {
	std::cout << "Hello World, i'm the cli!\n";

	Player test_player("Player Test");

	auto wooden_sword = std::make_unique<ItemWeapon>("Wooden Sword", "t");
	auto excalibur = std::make_unique<ItemWeapon>("Excalibur", "t");

	ItemID sword_id = wooden_sword->getID();
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
