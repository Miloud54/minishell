/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:07:37 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/13 17:09:02 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	init_expansion_context(t_copy_context *ctx, char *input,
		t_data *data, char *result)
{
	static int	i;
	static int	j;

	i = 0;
	j = 0;
	ctx->input = input;
	ctx->data = data;
	ctx->result = result;
	ctx->i = &i;
	ctx->j = &j;
}
