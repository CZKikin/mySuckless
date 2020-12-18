//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/						/*Update Interval*/	/*Update Signal*/
	{"", 		"pactl list sinks | awk '/^\\WHlasitost/ {print \" VOL \"$5}'",   0,		3},
	{"", 		"free -h | awk '/^Mem/ { print \" MEM \"$3\"/\"$7\"/\"$2 }' | sed s/i//g",	10,		1},
    {"", 		"date +\" %d.%m.%Y %H:%M:%S\"", 							1,     2},
    {"",        "[ `cat /sys/class/power_supply/BAT0/capacity` -lt 10 ] && notify-send \"A doprdele\" \"BATERKA DEBILE\" ; awk '{print \" BAT \"$1\"%\"}' /sys/class/power_supply/BAT0/capacity", 120, 4}
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
