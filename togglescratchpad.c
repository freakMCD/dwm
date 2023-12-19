static void toggleview_scratchpad(const Arg *arg) {
    Client *c;
	unsigned int scratchtag = SPTAG(arg->ui);

    for(c = selmon->clients; c; c = c->next) {
		if(c->tags & scratchtag) {
			if (c->issticky) {
			    setsticky(c, 0);
			    focusdefault(NULL);
			}
			else if (!c->issticky) {
			    setsticky(c, 1);
			    if(!c->ismpv)
			        focusdefault(c);
			}
			arrange(selmon);
	    }
    }

}

