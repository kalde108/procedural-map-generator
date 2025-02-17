/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_index.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:50:56 by ibertran          #+#    #+#             */
/*   Updated: 2024/10/26 16:42:35 by kchillon         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_INDEX_H
# define KEY_INDEX_H

# include <stdbool.h>

# define MOUSE_BUTTON_LEFT 1
# define MOUSE_BUTTON_RIGHT 2
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 8

enum e_keycode
{
	KEY_A = 0,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_ESC,
	KEY_SPACE,
	KEY_LEFT,
	KEY_UP,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_PLUS,
	KEY_MINUS,
	KEY_KP_ADD,
	KEY_KP_SUB,
	KEY_CTRL_L,
	KEY_SHIFT_L,
	KEY_RETURN,
	KEY_BACKSPACE,
	KEY_ALT_L,
	KEY_COUNT
};

typedef enum e_keystate
{
	KEY_STATE_IDLE = 0,
	KEY_STATE_PRESSED,
	KEY_STATE_HELD,
	KEY_STATE_RELEASED,
	KEY_STATE_COUNT
}	t_keystate;

int	get_keyindex(int keycode);

#endif
