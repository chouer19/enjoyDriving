#ifndef F710_H
#define F710_H


struct f710 {
        int _fd;
	double lx;
	double ly;
	double rx;
	double ry;
	double lt;
	double rt;
	int lb:1;
	int rb:1;
	int left:1;
	int right:1;
	int up:1;
	int down:1;
	int a:1;
	int b:1;
	int x:1;
	int y:1;
	int start:1;
	int back:1;
	int logitech:1;
	int ljb:1;
	int rjb:1;
};


/* Opens the joystick interface and initializes the structure. */
int f710_open(struct f710 *c, const char *path);

/* Closes the joystick interface.   */
int f710_close(struct f710 *c);

/* Wait for a new event and update the structure. Blocks until change. */
int f710_update(struct f710 *c);

/* Prints the state of the joystick to stdout. */
void f710_print(const struct f710 *c);


#endif /* F710_H */
