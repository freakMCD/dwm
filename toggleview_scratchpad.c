static void toggleview_scratchpad(const Arg *arg) {
    Client *c;
    for(c = selmon->clients; c; c = c->next) { 
        if(c->tags & arg->ui) {
            if (c->issticky) 
                setsticky(c, 0);
            else if (!c->issticky)
                setsticky(c, 1);
            arrange(selmon);
        }
    }
}
