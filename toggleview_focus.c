static void toggleview_focus(const Arg *arg) {
	Client *c;
	unsigned int newtagset = selmon->tagset[selmon->seltags] ^ (arg->ui & TAGMASK);

	if (newtagset) {
		selmon->tagset[selmon->seltags] = newtagset;
        for(c = selmon->clients; !(c->tags & arg->ui) && c->next; c = c->next);
        if(c && c->tags & arg->ui)
            focusdefault(c);
        else
            focus(NULL);
		arrange(selmon);
	}

}
