#include <err.h>
#include <fcntl.h>
#include <limits.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "f710.h"


/* Make a unique ID from an event. */
#define V2ID(n, t) (n << 8 | t)
#define E2ID(iev) V2ID(iev.number, iev.type)


int f710_open(struct f710 *c, const char *path)
{
        memset(c, 0, sizeof(*c));
        if ((c->_fd = open(path, O_RDONLY)) == -1)
                return -1;
        return 0;
}


int f710_close(struct f710 *c)
{
        return close(c->_fd);
}


int f710_update(struct f710 *c)
{
        struct js_event iev;
        int ret;

        ret = read(c->_fd, &iev, sizeof(iev));
        if (ret != sizeof(iev))
                return -1;

        switch (E2ID(iev)) {
        case V2ID(0, 1): c->a  = !!iev.value;                   break;
        case V2ID(0, 2): c->lx = iev.value / (double) SHRT_MAX; break;
        case V2ID(1, 1): c->b  = !!iev.value;                   break;
        case V2ID(1, 2): c->ly = iev.value / (double) SHRT_MAX; break;
        case V2ID(2, 1): c->x  = !!iev.value;                   break;
        case V2ID(2, 2):
                c->lt = (iev.value + SHRT_MAX) / (2.0 * SHRT_MAX);
                break;
        case V2ID(3, 1): c->y  = !!iev.value;                   break;
        case V2ID(3, 2): c->rx = iev.value / (double) SHRT_MAX; break;
        case V2ID(4, 1): c->lb = !!iev.value;                   break;
        case V2ID(4, 2): c->ry = iev.value / (double) SHRT_MAX; break;
        case V2ID(5, 1): c->rb = !!iev.value;                   break;
        case V2ID(5, 2):
                c->rt = (iev.value + SHRT_MAX) / (2.0 * SHRT_MAX);
                break;
        case V2ID(6, 1): c->back = !!iev.value;                 break;
        case V2ID(6, 2):
                c->left  = (iev.value == -SHRT_MAX);
                c->right = (iev.value ==  SHRT_MAX);
                break;
        case V2ID(7, 1): c->start = !!iev.value;                break;
        case V2ID(7, 2):
                c->up   = (iev.value == -SHRT_MAX);
                c->down = (iev.value ==  SHRT_MAX);
                break;
        case V2ID(8, 1): c->logitech = !!iev.value;             break;
        case V2ID(9, 1): c->ljb      = !!iev.value;             break;
        case V2ID(10, 1): c->rjb     = !!iev.value;             break;
        }

        return 0;
}


void f710_print(const struct f710 *c)
{
        printf(" __________                         _________ \n"
               "|    %3.1f   |                       |   %3.1f   |\n"
               "|    %u     |                       |   %u     |\n"
               "|--------------------------------------------|\n"
               "|    %u           %u    %u    %u           %u     |\n"
               "| %u     %u        x         x        %u     %u  |\n"
               "|    %u                                 %u     |\n"
               "|          %+3.1f               %+3.1f           |\n"
               "|          %+3.1f               %+3.1f           |\n"
               "|           %u                  %u             |\n",
               c->lt, c->rt, !!c->lb, !!c->rb, !!c->up, !!c->back,
               !!c->logitech, !!c->start, !!c->y, !!c->left,
               !!c->right, !!c->x, !!c->b, !!c->down, !!c->a, c->lx,
               c->rx, c->ly, c->ry, !!c->ljb, !!c->rjb);
}
