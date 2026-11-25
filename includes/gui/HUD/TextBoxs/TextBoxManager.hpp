/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBoxManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 15:21:42 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/25 15:58:07 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "raylib.h"

// Singleton class
class TextBoxManager {
    private:
		Texture2D	hud_texture;

        TextBoxManager() {} //private constructor to bloc external instantiation
        
        TextBoxManager(const TextBoxManager &textb) = delete; // copy constructor removed to avoid external copy
        TextBoxManager& operator=(const TextBoxManager &textb) = delete; // "=" opperator removed to guess what.... avoid external copy
    
    public:
        // access the unique instance
        static TextBoxManager &access() {
            static TextBoxManager text_box;
            return (text_box);
        }
};