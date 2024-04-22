/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavila- <adavila-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:49:28 by adavila-          #+#    #+#             */
/*   Updated: 2024/04/18 21:49:28 by adavila-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

// Map parsing errors
# define BAD_CHAR "Found an invalid character while parsing the map"
# define BAD_CLOSE "Map must be enclosed with walls!"
# define BAD_LINE "All lines must have the same length!"
# define BAD_GEOMETRY "Map must not be a square!"
# define BAD_SPAWN "There must be only 1 spawn point and 1 exit!"
# define NULL_COLLECTS "No collectables were found!"
# define NO_WALK "The map must have a walkable path!"
// In-game errors

#endif