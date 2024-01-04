static void toggleview_scratchpad(const Arg *arg) {
    Client *c;
	unsigned int scratchtag = SPTAG(arg->ui);

    for(c = selmon->clients; c; c = c->next) {
	    if(c->tags & scratchtag) {
			if (c->issticky) {
	            if (c->isfullscreen)
	                setfullscreen(c,0);
			    setsticky(c, 0);
			    focusdefault(NULL);
			}
			else if (!c->issticky) {
			    setsticky(c, 1);
			    if(!c->ismpv || c->isfullscreen)
			        focusdefault(c);
			}
	        arrange(selmon);
		}
    }
}


