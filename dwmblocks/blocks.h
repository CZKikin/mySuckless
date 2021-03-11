//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/	                                /*Update Interval*/	/*Update Signal*/
	{"", 		"~/.scripts/statusScripts/volume",          0,          		3},
	//{"", 		"~/.scripts/statusScripts/memory",	        10,         		1},
    {"", 		"~/.scripts/statusScripts/date",            1,                  2},
    {"",        "~/.scripts/statusScripts/battery",         15,                 4}
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
