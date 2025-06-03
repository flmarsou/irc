/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:47:19 by flmarsou          #+#    #+#             */
/*   Updated: 2025/06/03 12:52:58 by flmarsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

# define ERROR		"\e[31m[x] - Error: \e[0m"
# define SUCCESS	"\e[32m[v] - Success: \e[0m"
# define WARNING	"\e[35m[!] - Warning: \e[0m"
# define INFO		"\e[36m[i] - Info: \e[0m"
# define MSG		"\e[33m[#] - Message: \e[0m"
# define CMD(cmd)	"\e[34m[/] - " + cmd + ": \e[0m"
