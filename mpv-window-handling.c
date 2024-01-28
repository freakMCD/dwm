// Patch for handling mpv windows
// In config.h, A rule that assigns mpv clients to a dedicated SPTAG, keeping them independent of regular tags.
// In dwm.c, searching "mpv" should be enough to find related modifications

/* Function to get the PID of the given client and call a script
 * Called in manage(), unmanage(), zoom(), togglesticky, togglestickympv() 
 * ChatGPT 3.5 helped me with this function */
void
autoplaympv(Window win)
{
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned char *prop = NULL;

    // Check if the property is retrieved successfully and is of the expected type and format
    if (XGetWindowProperty(dpy, win, XInternAtom(dpy, "_NET_WM_PID", False), 0L, 1L, False,
                           AnyPropertyType, &actual_type, &actual_format, &nitems, &bytes_after, &prop) != Success)
        return;

    if (prop && actual_type == XA_CARDINAL && actual_format == 32 && nitems > 0) {
        // Extract the PID from the property
        pid_t pid = *((pid_t *)prop);

        // Free the property memory
        XFree(prop);

        // Fork and exec to run the script asynchronously
        pid_t child_pid = fork();

        if (child_pid == 0) {
            // This is the child process
            char cmd[256];
            snprintf(cmd, sizeof(cmd), "mpvPlayControl.sh %d", pid);
            execl("/bin/sh", "/bin/sh", "-c", cmd, (char *)0);
            _exit(1); // In case execl fails
        }
    }
}

void togglefullscrmpv(const Arg *arg) {
    Client *c;
    for (c = selmon->clients; c && !(c->ismpv && ISVISIBLE(c)); c = c->next);

    if (c) {
        setfullscreen(c, !c->isfullscreen);
        focus(c->isfullscreen ? c : NULL);
    }
}

static void togglestickympv(const Arg *arg) {
    Client *c;
    for (c = selmon->clients; c; c = c->next) {
        if (c->ismpv) {
            setsticky(c, !c->issticky);

            if (c->isfullscreen)
                focusdefault(c);
            else
                focus(NULL);
        }
    }

    arrange(selmon);

    // Find the next tiled client that is both mpv and visible
    Client *tc;
    for (tc = selmon->clients; tc && (!ISVISIBLE(tc) || !tc->ismpv ); tc = tc->next);
    if(tc) {
        autoplaympv(tc->win);
    }
}




