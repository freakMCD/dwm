static void toggleview_scratchpad(const Arg *arg) {
    Client *c;
	for(c = selmon->clients; !(c->tags & arg->ui) && c->next; c = c->next) ;
    if (ISVISIBLE(c)) 
        c->issticky=0;
    else 
        c->issticky=1;
    arrange(selmon);
}
