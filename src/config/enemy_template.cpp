/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_template.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:41:20 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/10 10:10:17 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unordered_map>

# include "config/EnemyTemplate.hpp"
# include "config/Enums.hpp"


const EnemyTemplate* find_enemy_template(const std::string& entity_id) {
	static const std::unordered_map<std::string, EnemyTemplate>	enemies_map {
		// --- VIROVIROKUN ---
		{ "virovirokun", { EnemyBehavior::VIROVIROKUN, 3, {
			{ "encounter", "Virovirokun floated in!" },
			{ "check_default", "The sick virus needs affordable healthcare." },
			{ "neutral_1", "Virovirokun is sweating suspiciously." },
			{ "neutral_2", "Virovirokun uses a text document as a tissue." },
			{ "neutral_3", "Virovirokun is poking round things with a spear." },
			{ "neutral_4", "Virovirokun is beeping a criminal tune." },
			{ "neutral_5", "Smells like cherry syrup." },
			{ "act_1", "You treated Virovirokun with a big smile. It's less infectious !" },
			{ "act_2", "You treated Virovirokun with joy. It's less infectious !" },
			{ "act_3", "You treated Virovirokun with care! It's no longer infectious!" },
			{ "low_hp", "Virovirokun looks extra sick." },
			{ "can_spare", "Virovirokun looks healthy." }
		} } },

		// --- MAUS ---
		{ "maus", { EnemyBehavior::MAUS, 1, {
			{ "encounter", "Maus blocked the way!" },
			{ "check_default", "It's just a little mouse living in a little house. But they are too much." },
			{ "neutral_1", "Maus is clicking and squeaking." },
			{ "neutral_2", "Maus is thinking about overly elaborate machines." },
			{ "neutral_3", "Maus keeps running between your feet." },
			{ "neutral_4", "Maus is keenly aware of the fear it invokes." },
			{ "neutral_5", "Maus would like to go to its favorite bistro in this marvelous city." },
			{ "neutral_6", "Smells like wood shavings." },
			{ "act_1", "Press [(SPACE)] To Trap!!!" },
			{ "act_result_failed", "Didn't catch anything..." },
			{ "act_result_won", "Caught the enemy!" },
			{ "low_hp", "Maus's clicking sounds more like splat noises." },
			{ "can_spare", "Maus is squeaking cheerfully." }
		} } },

		// --- KAWKAW ---
		{ "kawkaw", { EnemyBehavior::KAWKAW, 1, {
			{ "encounter", "Kawkaw wants to play! Help him!" },
			{ "check_default", "It thinks battle is play. Loves scarecrows. " },
			{ "neutral_1", "Kawkaw pecks the ground looking for treats." },
			{ "neutral_2", "Kawkaw wants to play with a throwing toy." },
			{ "neutral_3", "Kawkaw makes ueueueueue noises." },
			{ "neutral_4", "Kawkaw gathers sticks for nest and fetch." },
			{ "act_1", "Press [(SPACE)] To Find!!!" },
			{ "act_result_failed", "Bad number..." },
			{ "act_result_won", "Good number!" },
			{ "low_hp", "Kawkaw is licking its wounds." },
			{ "can_spare", "Kawkaw is ready to sleep in a nest. " }
		} } },

		// --- SWATCHLINGS ---
		{ "swatchlings", { EnemyBehavior::SWATCHLINGS, 3, {
			{ "encounter", "Swatchlings bowed in!" },
			{ "check_default", "Happiest when their outfits are color-coordinated." },
			{ "neutral_1", "The Swatchlings wipe at the face of their chained pocketwatch, which is digital." },
			{ "neutral_2", "Smells like paint and feathers." },
			{ "neutral_3", "The Swatchlings are cleaning each other off with feather dusters." },
			{ "neutral_4", "Swatchlings flex their backs while bending over to inspect a teacup." },
			{ "neutral_5", "The Swatchlings are adjusting their hue and saturation." },
			{ "act_coldify_1", "Talked about the crunch of the last pickle in the refrigerator." },
			{ "act_coldify_2", "Talked about the chill of the wind on an ice skating pond." },
			{ "act_coldify_3", "Talked about the snow matted on your brother's nose." },
			{ "act_warmify_1", "Talked about the color of the summer sun shining on a beach ball." },
			{ "act_warmify_2", "Talked about the steam of a fresh hot chocolate." },
			{ "act_warmify_3", "Talked about the warmth of a loving embrace." },
			{ "act_check_oufit_half_warm", "Swatchling's color got a little bit warmer...!" },
			{ "act_check_oufit_half_cold", "Swatchling's color turned a lot/a little bit colder...!" },
			{ "act_check_oufit_nothing", "But Swatchling is already as warm/cold as can be!" },
			{ "act_check_oufit_green", "Swatchling's as become like grass." },
			{ "act_check_oufit_orange", "Swatchling's as become like a clementine." },
			{ "act_check_oufit_yellow", "Swatchling's as become like a banana." },
			{ "act_check_oufit_red", "Swatchling's as become like an apple." },
			{ "low_hp", "The Swatchling is dreading doing all of the work by itself." },
			{ "can_spare", "The Swatchlings are relieved their wardrobe has been coordinated. " }
		} } },

		// --- GUARD DOG ---
		{ "guard_dog", { EnemyBehavior::GUARD_DOG, 12, {
			{ "talk_1", "You shall not pass as I guard those gates." },
			{ "talk_2", "(even if you can pass by just going around...)." },
			{ "talk_3", "But if you want to pass. You shall met my delicious strength." },
			{ "talk_4", "Are you sure you want to fight me?" },
			{ "talk_5", "In reality I've lost the other remote of the gates. I can't let you pass." },
			{ "talk_6", "I've have one but it's mine." },
			{ "talk_7", "Are you sure you want to force you way through?" },
			{ "talk_8", "You have the remote. You shall pass." },
			{ "encounter", "This is a dog in a guard suit." },
			{ "check_default", "It's not very excited." },
			{ "check_1", "It's a bit excited." },
			{ "check_2", "It's excited but not enought to play." },
			{ "check_3", "It's so excited that it thinks fighting is just play." },
			{ "neutral_1", "Guard Dog is watching you intently." },
			{ "neutral_2", "Guard Dog is waiting for your command." },
			{ "neutral_3", "It smells like freshly-squeezed puppy juice." },
			{ "neutral_4", "Guard Dog is seeking affection." },
			{ "act_pet_1", "Greater Dog is too far away to pet. You just pet the air." },
			{ "act_pet_2", "You pet the dog." },
			{ "act_play_1", "Greater Dog is not excited enough to play with." },
			{ "act_play_2", "You play with the dog." },
			{ "act_ignore", "You ignore the dog. His face looks sad." },
			{ "low_hp", "Greater Dog is panting slowly." },
			{ "can_spare", "Greater Dog is contented." },
			{ "killed", "I... just wanted the ball..." }
		} } },

		// --- K.ROUND ---
		{ "k_round", { EnemyBehavior::K_ROUND, 15, {
			{ "talk_1", "K.Round look at you. He thinks you are special." },
			{ "talk_2", "It give you a Key as a reward." },
			{ "talk_3", "K.Round look at you and smile. Only his mustache move." },
			{ "encounter", "K.Round shuffles furiously." },
			{ "check_default", "His crown is his source of power." },
			{ "neutral_1", "K.Round shuffles furiously." },
			{ "neutral_2", "K.Round is furious." },
			{ "neutral_3", "K.Round blocks the way." },
			{ "neutral_4", "K.Round is rolling around." },
			{ "act_bow", "You bowed to K. ROUND." },
			{ "act_bow_result", "It bowed back. Its crown loosened a little." },
			{ "check_bow_1", "Its crown start to move." },
			{ "check_bow_2", "Its crown is moving." },
			{ "check_bow_3", "Its crown is at the edge." },
			{ "check_bow_4", "Its crown start to fall." },
			{ "low_hp", "K.Round's shuffle becomes lethargic." },
			{ "spare", "K.Round lose his crown. He run away." }
		} } },

		// --- QUEEN ---
		{ "queen", { EnemyBehavior::QUEEN, 20, {
			{ "talk_1", "Oh! You're finally here!" },
			{ "talk_2", "Congratulation. You want your moss?" },
			{ "talk_3", "Distract me and I will give it to you." },
			{ "talk_4", "Wants to fight?" },
			{ "talk_5", "Well. Well. Well." },
			{ "talk_6", "You won. Congrats. I just wanted to play with you. I'm bored." },
			{ "talk_7", "Take your moss now." },
			{ "talk_8", "You can go now." },
			{ "encounter", "The tension feels electric." },
			{ "check_default", "The Queen. Defeat is unknown to her." },
			{ "neutral_1", "The skyline echoes with regal laughter." },
			{ "neutral_2", "The fountain flows ominously." },
			{ "neutral_3", "Smells like overclocked high heels." },
			{ "neutral_4", "Moss feels you with DETERMINATION." }
		} } }
	};

	const auto it = enemies_map.find(entity_id);
	if (it == enemies_map.end())
		return nullptr;
	return &it->second;
}
