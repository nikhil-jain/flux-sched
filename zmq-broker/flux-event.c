/* flux-event.c - flux event subcommand */

#define _GNU_SOURCE
#include <getopt.h>
#include <json/json.h>
#include <assert.h>
#include <libgen.h>

#include "cmb.h"
#include "util.h"
#include "zmsg.h"
#include "log.h"

#define OPTIONS "hp:s"
static const struct option longopts[] = {
    {"help",       no_argument,        0, 'h'},
    {"publish",    required_argument,  0, 'p'},
    {"subscribe",  no_argument,        0, 's'},
    { 0, 0, 0, 0 },
};

void usage (void)
{
    fprintf (stderr, 
"Usage: flux-event --pub message [json]\n"
"       flux-event --sub [topic]\n"
);
    exit (1);
}

int main (int argc, char *argv[])
{
    flux_t h;
    int ch;
    char *arg = NULL;
    zmsg_t *zmsg;
    char *pub = NULL;
    bool sub = false;

    log_init ("flux-event");

    while ((ch = getopt_long (argc, argv, OPTIONS, longopts, NULL)) != -1) {
        switch (ch) {
            case 'h': /* --help */
                usage ();
                break;
            case 'p': /* --publish message [json] */
                pub = optarg;
                break;
            case 's': /* --subscribe [topic] */
                sub = true;
                break;
            default:
                usage ();
                break;
        }
    }
    if (optind != argc && optind != argc - 1)
        usage ();
    if (optind == argc - 1)
        arg = argv[optind];
    if (!pub && !sub)
        usage ();

    if (!(h = cmb_init ()))
        err_exit ("cmb_init");

    if (pub) {
        json_object *o = NULL;
        enum json_tokener_error e;
        if (arg && !(o = json_tokener_parse_verbose (arg, &e)))
            msg_exit ("json parse error: %s", json_tokener_error_desc (e));
        if (flux_event_send (h, o, "%s", pub) < 0 )
            err_exit ("flux_event_send");
        if (o)
            json_object_put (o);
    }
    if (sub) {
        if (flux_event_subscribe (h, arg) < 0)
            err_exit ("flux_event_subscribe");
        while ((zmsg = flux_event_recvmsg (h, false))) {
            zmsg_dump_compact (zmsg);
            zmsg_destroy (&zmsg);
        }
        if (flux_event_unsubscribe (h, arg) < 0)
            err_exit ("flux_event_unsubscribe");
    }

    flux_handle_destroy (&h);
    log_fini ();
    return 0;
}

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */