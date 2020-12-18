/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"minecraft:size=14",
    "ttf-NotoEmoji-Regular:pixelsize=12",
    "symbola:pixelsize=12",
    "Noto Sans Mono:pixelsize=12",
    "Noto Sans Display:pixelsize=12",
    "Noto Sans:pixelsize=12"
};
static const char *prompt      = "Vyber:";      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#FF0000", "#000000" },
	[SchemeSel] = { "#FFFFFF", "#000000" },
	[SchemeOut] = { "#000000", "#00ffff" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
