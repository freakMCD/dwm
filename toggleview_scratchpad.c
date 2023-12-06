static void toggleview_scratchpad(const Arg *arg) {
    Client *c;

    for(c = selmon->clients; c; c = c->next) {
		if(c->tags & SPTAG(arg->ui)) {
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

