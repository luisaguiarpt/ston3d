/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:34:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 10:34:35 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	init_input(t_core *core)
{
	core->input.w = false;
	core->input.a = false;
	core->input.s = false;
	core->input.d = false;
	core->input.left = false;
	core->input.right = false;
	core->input.click = false;
}
