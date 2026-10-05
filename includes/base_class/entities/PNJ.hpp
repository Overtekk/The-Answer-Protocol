/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PNJ.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/05 14:00:25 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include "Entity.hpp"

class PNJ : public Entity {
    private:
        /* data */
    public:
        // Constructor
        PNJ(const std::string& name, const fs::path& sprite, int health);

        // Destructor
        ~PNJ() = default;
};
