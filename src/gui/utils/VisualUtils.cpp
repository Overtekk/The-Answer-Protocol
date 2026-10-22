/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 11:03:26 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/22 11:17:10 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check for collision between any type of object if they have at least coordinates
// and size
bool checkCollison(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if ((x1 + w1 / 2 > x2 - w2 / 2 and x1 - w1 / 2 < x2 + w2 / 2)
	and (y1 + h1 / 2 > y2 - h2 / 2 and y1 - h1 / 2 < y2 + h2 / 2))
		return (true);
	return (false);
}