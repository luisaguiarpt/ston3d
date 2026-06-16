/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:49:50 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 17:09:22 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# define ERR_XPM "failed to load XPM texture"
# define ERR_DATA_ADDR "failed to get texture data address"

# define ERR_READ "unable to read .cub file"
# define ERR_MEMORY "not enough memory"
# define ERR_FORMAT "textures must be .xpm files"
# define ERR_WALLS "map must be closed/surrounded by walls"
# define ERR_COLOR_FORMAT "wrong format, could not load colour"
# define ERR_COLOR_VALUE "colour values must be between 0 and 255"
# define ERR_COLOR_COUNT "colour definition expects 3 values (R, G, B)"
# define ERR_COMMA "comma expected between colour values"
# define ERR_TEXTURE "unable to find textures from the .cub file"
# define ERR_TOO_MANY_PLAYERS "map can't have more than one player spawn point"
# define ERR_NO_PLAYER "no player found"
# define ERR_FORBIDDEN_CHAR "only the characters ' ', '0', '1', 'N', 'S', 'E' and 'W' are valid for the map"

// bonus errors
# define ERR_COLL_NUM "map must have exactly one 'a', one 'b', one 'c'"
# define ERR_TOO_MANY_COLL "too many collectibles in map"

#endif
