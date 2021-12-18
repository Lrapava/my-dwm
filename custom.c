// #include <X11/XF86keysym.h>
#include "xevkeys.h"
#include <stddef.h>
#include <stdlib.h>

int compositor_running = 1, curkb = 0;

static const char *mutecmd[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *volupcmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutemic[] = { "amixer", "set", "Capture", "toggle", NULL };
static const char *phone_gallery[] = { "pcmanfm", "/home/lrapava/Pictures/Android Camera/Camera", NULL };
static const char *slock[] = { "./lock.sh", NULL };

static const char *browser[] = { "brave-browser", NULL };
static const char *steam[] = { "steam", NULL};
static const char *screenshot[] = { "flameshot", "gui", NULL };
// static const char *rect_screenshot[] = { "scrot", "-s", NULL };

static const char *settings[] = { "./settings.sh", NULL };
// static const char *quickshell[] = { "./quickshell.sh", NULL };

// start/kill compositor
static void skcomp() {
	if (compositor_running) system("killall picom"); else system("picom --config ~/projects/picom/picom.sample.conf &");
	compositor_running = (compositor_running + 1) % 2;
}

static const char *keyboard_layouts[] = {"setxkbmap us", "setxkbmap ge"};

static void kbmanage() {
	curkb = (curkb + 1) % (sizeof(keyboard_layouts) / sizeof(keyboard_layouts[0]));
	system(keyboard_layouts[curkb]);
}
