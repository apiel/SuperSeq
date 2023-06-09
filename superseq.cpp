#include "def.h"
#include "config.h"
#include "msg.h"
#include "seq.h"
#include "step.h"
#include "loop.h"

int done = 0;

void error(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
    fflush(stdout);
}

int quit_handler(const char *path, const char *types, lo_arg ** argv,
                 int argc, lo_message data, void *user_data)
{
    done = 1;
    printf("quiting\n");
    return 0;
}

int main()
{
    lo_server_thread serverThread = lo_server_thread_new(port, error);

    printf("SuperSeq listening on port %s\n", port);

    lo_server server = lo_server_thread_get_server(serverThread);

    lo_server_thread_add_method(serverThread, "/seq", "iii", seq_handler, NULL);
    lo_server_thread_add_method(serverThread, "/step", "iiiiiii", step_handler, NULL);
    lo_server_thread_add_method(serverThread, "/msg", NULL, msg_handler, NULL);
    lo_server_thread_add_method(serverThread, "/msg_get", "i", msg_get_handler, server);
    lo_server_thread_add_method(serverThread, "/msg_arg", NULL, msg_arg_handler, NULL);
    lo_server_thread_add_method(serverThread, "/sub", NULL, sub_handler, NULL);
    lo_server_thread_add_method(serverThread, "/quit", "", quit_handler, NULL);

    lo_server_thread_start(serverThread);

    while (!done) {
        loop();
    }

    lo_server_thread_free(serverThread);

    return 0;
}
