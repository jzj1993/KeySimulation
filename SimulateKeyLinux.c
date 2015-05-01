#include <linux/input.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void simulate_key(int fd, unsigned int keycode, int keyvalue)
{
	struct input_event event;

	event.type = EV_KEY;
	event.code = keycode;
	event.value = keyvalue;
	gettimeofday(&event.time, 0);

	if (write(fd, &event, sizeof(event)) < 0) {
		printf("simulate key error\n");
	} else {
		printf("simuate key %d, %d\n", keycode, keyvalue);
	}
}

int main ( int argc, char *argv[] )
{
	int i;
	char *path = "/dev/input/event2";
	unsigned int key_code = KEY_ENTER;   //¼üÖµ: Enter
	// unsigned int key_code = KEY_NUMLOCK;   //¼üÖµ: NumLock
	// unsigned int key_code = KEY_A;        //¼üÖµ£ºa

	// if (argc >= 3) {
		// path = argv[1];
		// key_code = atoi(argv[2]);
	// } else if (argc >= 2) {
		// path = argv[1];
	// }

	int fd_kbd = open(path, O_RDWR);

	if(fd_kbd <= 0) {
		printf("error open keyboard:%s\n", strerror(errno));
		return -1;
	}

	for(i = 0; i < 10; ++i) {
		simulate_key(fd_kbd, key_code, 1);
		simulate_key(fd_kbd, key_code, 0);
		sleep(1);
	}

	close(fd_kbd);

	return 0;
}
