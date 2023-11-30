static void toggleview_focus(const Arg *arg) {
	Client *c;
	toggleview(arg);
  	for(c = selmon->clients; !(c->tags & arg->ui) && c->next; c = c->next) ;
	if(c && c->tags & arg->ui) {
        XRaiseWindow(dpy, c->win);
        if (ISVISIBLE(c)) {
            focus(c);
            restack(selmon);
        }
		focus(NULL);
        arrange(selmon);
    }
}
