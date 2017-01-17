#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include "../config.h"
#include "../interface/keyboard_shortcut.h"
#include "../interface/themes.h"
#include "../interface/window.h"
#include "../interface/widget.h"
#include "../localisation/localisation.h"

extern const rct_string_id ShortcutStringIds[];

#define WW 250
#define WH 60

enum WINDOW_SHORTCUT_CHANGE_WIDGET_IDX {
	WIDX_BACKGROUND,
	WIDX_TITLE,
	WIDX_CLOSE,
};

// 0x9DE4E0
static rct_widget window_shortcut_change_widgets[] = {
	{ WWT_FRAME,			0,	0,			WW - 1,	0,		WH - 1,		STR_NONE,					STR_NONE },
	{ WWT_CAPTION,			0,	1,			WW - 2,	1,		14,			STR_SHORTCUT_CHANGE_TITLE,	STR_WINDOW_TITLE_TIP },
	{ WWT_CLOSEBOX,			0,	WW-13,		WW - 3,	2,		13,			STR_CLOSE_X,				STR_CLOSE_WINDOW_TIP },
	{ WIDGETS_END }
};

static void window_shortcut_change_mouseup(rct_window *w, sint32 widgetIndex);
static void window_shortcut_change_invalidate(rct_window *w);
static void window_shortcut_change_paint(rct_window *w, rct_drawpixelinfo *dpi);

//0x9A3F7C
static rct_window_event_list window_shortcut_change_events = {
	NULL,
	window_shortcut_change_mouseup,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	window_shortcut_change_invalidate,
	window_shortcut_change_paint,
	NULL
};

void window_shortcut_change_open(sint32 selected_key){
	// Move this to window_shortcut_change_open
	window_close_by_class(WC_CHANGE_KEYBOARD_SHORTCUT);
	// Save the item we are selecting for new window
	gKeyboardShortcutChangeId = selected_key;
	rct_window* w = window_create_centred(WW, WH, &window_shortcut_change_events, WC_CHANGE_KEYBOARD_SHORTCUT, 0);

	w->widgets = window_shortcut_change_widgets;
	w->enabled_widgets = (1 << 2);
	window_init_scroll_widgets(w);
}

/**
*
*  rct2: 0x006E3AE0
*/
static void window_shortcut_change_mouseup(rct_window *w, sint32 widgetIndex)
{
	switch (widgetIndex){
	case WIDX_CLOSE:
		window_close(w);
		break;
	}
}

static void window_shortcut_change_invalidate(rct_window *w)
{
	colour_scheme_update(w);
}

/**
*
*  rct2: 0x006E3A9F
*/
static void window_shortcut_change_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);

	sint32 x = w->x + 125;
	sint32 y = w->y + 30;

	set_format_arg(0, rct_string_id, ShortcutStringIds[gKeyboardShortcutChangeId]);
	gfx_draw_string_centred_wrapped(dpi, gCommonFormatArgs, x, y, 242, STR_SHORTCUT_CHANGE_PROMPT, COLOUR_BLACK);
}