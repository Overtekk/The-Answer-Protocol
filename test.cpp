# include <iostream>
# include <iomanip>
# include <random>
# include <algorithm>
# include <string>
# include <vector>


static constexpr float	BASE_LUCK_FLEE = 0.5f;
static constexpr float	BASE_RATIO_ENEMY_HP_FLEE = 20.0f;
static constexpr float	BASE_RATIO_PLAYER_HP_FLEE = 15.0f;
static constexpr float	MIN_CHANCE = 20.0f;
static constexpr float	MAX_CHANCE = 90.0f;

struct Scenario {
	std::string	name;
	int			luck;
	int			player_hp;
	int			player_max_hp;
	int			enemy_hp;
	int			enemy_max_hp;
};

// * Same maths as tryFlee, but returns the percentage instead of rolling. *
float	computeChance(const Scenario& s) {
	float flee_base_chance = 50.0f;
	float player_bonus_chance = s.luck * BASE_LUCK_FLEE;
	float ratio_enemy = ((static_cast<float>(s.enemy_hp) / s.enemy_max_hp) * BASE_RATIO_ENEMY_HP_FLEE);
	float ratio_player = ((static_cast<float>(s.player_hp) / s.player_max_hp) * BASE_RATIO_PLAYER_HP_FLEE);
	flee_base_chance += player_bonus_chance - ratio_enemy - ratio_player;

	return std::clamp(flee_base_chance, MIN_CHANCE, MAX_CHANCE);
}

int	main() {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> roll_100(0, 99);
	const int ROLLS = 100000;

	std::vector<Scenario> scenarios = {
		//  name                              luck  p_hp p_max  e_hp e_max
		{"neutre (luck 10, tout plein)",       10,  100, 100,  142, 142},
		{"pire cas (luck 0, tout plein)",       0,  100, 100,  142, 142},
		{"meilleur cas (luck 50, J bas)",      50,    1, 100,    1, 142},
		{"ennemi a 100%",                      10,   50, 100,  142, 142},
		{"ennemi a 50%",                       10,   50, 100,   71, 142},
		{"ennemi a 10%",                       10,   50, 100,   14, 142},
		{"joueur a 100%",                      10,  100, 100,   71, 142},
		{"joueur a 50%",                       10,   50, 100,   71, 142},
		{"joueur a 10%",                       10,   10, 100,   71, 142},
		{"luck 0",                              0,   50, 100,   71, 142},
		{"luck 10",                            10,   50, 100,   71, 142},
		{"luck 30",                            30,   50, 100,   71, 142},
		{"petit ennemi (20 PV, plein)",        10,   50, 100,   20,  20},
		{"boss (500 PV, plein)",               10,   50, 100,  500, 500},
	};

	std::cout << std::fixed << std::setprecision(1);
	std::cout << std::left << std::setw(34) << "scenario"
		<< std::right << std::setw(10) << "formule" << std::setw(12) << "mesure" << "\n";
	std::cout << std::string(56, '-') << "\n";

	for (const Scenario& s : scenarios) {
		float chance = computeChance(s);

		int success = 0;
		for (int i = 0; i < ROLLS; ++i)
			if (roll_100(rng) < chance)
				++success;

		std::cout << std::left << std::setw(34) << s.name
			<< std::right << std::setw(9) << chance << "%"
			<< std::setw(11) << (100.0f * success / ROLLS) << "%\n";
	}
}

// c++ -std=c++17 -Wall -Wextra -Werror test.cpp -o test && ./test
