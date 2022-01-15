// #include <X11/XF86keysym.h>
#include "xevkeys.h"
#include <stddef.h>
#include <stdlib.h>

int gaming_mode = 0, curkb = 0;

// static const char *volupcmd[]        = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
// static const char *voldowncmd[]      = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
// static const char *mutecmd[]         = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *mutecmd[]         = { "pulsemixer", "--toggle-mute", NULL };
static const char *voldowncmd[]      = { "pulsemixer", "--change-volume", "-5", NULL };
static const char *volupcmd[]        = { "pulsemixer", "--change-volume", "+5", NULL };
static const char *mutemic[]         = { "amixer", "set", "Capture", "toggle", NULL };
static const char *phone_gallery[]   = { "pcmanfm", "/home/lrapava/Pictures/Android Camera/Camera", NULL };
static const char *slock[]           = { "./lock.sh", NULL };
static const char *browser[]         = { "brave-browser", NULL };
static const char *steam[]           = { "steam", NULL};
static const char *screenshot[]      = { "flameshot", "gui", NULL };

// static const char *rect_screenshot[] = { "scrot", "-s", NULL };
// static const char *settings[]        = { "./settings.sh", NULL };
// static const char *quickshell[]      = { "./quickshell.sh", NULL };

// start/kill compositor
static void toggle_gaming_mode() {
	if (!gaming_mode) system("killall picom ; killall syncthing ; xrandr -s 1280x720"); 
	// picom --config ~/import/projects/picom/picom.sample.conf &
	else system("syncthing -no-browser -logfile=/home/lrapava/syncthing-log & xrandr -s 1920x1080 -r 75");
	gaming_mode = (gaming_mode + 1) % 2;
}

void onStart() {
	system("dwm_startup");
}

void onExit() {
	system("killall syncthing");
}

static const char *keyboard_layouts[] = {"setxkbmap us", "setxkbmap ge"};

static void kbmanage() {
	curkb = (curkb + 1) % (sizeof(keyboard_layouts) / sizeof(keyboard_layouts[0]));
	system(keyboard_layouts[curkb]);
}
