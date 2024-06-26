#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"

#define BUFSIZE 1024

enum
{
    STATE_R = 1,
    STATE_W,
    STATE_E,
    STATE_T
};

struct fsm_st
{
    int state;
    int sfd;
    int dfd;
    char buf[BUFSIZE];
    int len;
    int pos;
    char *errstr;
};

void
fsm_driver(struct fsm_st *fsm)
{
    int ret;
    switch (fsm->state)
    {
    case STATE_R:
        ret = read(fsm->sfd, fsm->buf, BUFSIZE);
        if (ret < 0)
        {
            if (errno == EAGAIN)
                fsm->state = STATE_R;
            else
            {
                fsm->errstr = "read()";
                fsm->state = STATE_E;
            }
        }
        else if (ret == 0)
        {
            fsm->state = STATE_T;
        }
        else
        {
            fsm->state = STATE_W;
            fsm->len = ret;
            fsm->pos = 0;
        }
        break;
    case STATE_W:
        ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
        if (ret < 0)
        {
            if (errno == EAGAIN)
                fsm->state = STATE_W;
            else
            {
                fsm->errstr = "write()";
                fsm->state = STATE_E;
            }
        }
        else
        {
            if (ret < fsm->len)
            {
                fsm->pos += ret;
                fsm->len -= ret;
                fsm->state = STATE_W;
            }
            else
                fsm->state = STATE_R;
        }
        break;
    case STATE_E:
        perror(fsm->errstr);
        fsm->state = STATE_T;
        break;
    case STATE_T:
        break;
    default:
        abort();
    }
}

void
relay(int fd1, int fd2)
{
    int fd1_save, fd2_save;
    struct fsm_st fsm12, fsm21;

    fd1_save = fcntl(fd1, F_GETFL);
    fcntl(fd1, F_SETFL, fd1_save | O_NONBLOCK);

    fd2_save = fcntl(fd2, F_GETFL);
    fcntl(fd2, F_SETFL, fd2_save | O_NONBLOCK);

    fsm12.state = STATE_R;
    fsm12.sfd = fd1;
    fsm12.dfd = fd2;

    fsm21.state = STATE_R;
    fsm21.sfd = fd2;
    fsm21.dfd = fd1;

    while (fsm12.state != STATE_T || fsm21.state != STATE_T)
    {
        fsm_driver(&fsm12);
        fsm_driver(&fsm21);
    }

    fcntl(fd1, F_SETFL, fd1_save);
    fcntl(fd2, F_SETFL, fd2_save);
}

int
main()
{
    int fd1, fd2;

    fd1 = open(TTY1, O_RDWR);
    if (fd1 < 0)
    {
        perror("open()");
        exit(1);
    }

    write(fd1, "TTY1\n", 5);

    fd2 = open(TTY2, O_RDWR);
    if (fd2 < 0)
    {
        perror("open()");
        exit(1);
    }

    write(fd2, "TTY2\n", 5);

    relay(fd1, fd2);

    close(fd1);
    close(fd2);
    exit(0);
}