/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:02:39 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 16:37:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "command.h"

t_command	*parse(t_token *token);
size_t		cmd_lst_size(t_command *cmd);
void		cmd_lst_clear(t_command **cmd);;

#endif
