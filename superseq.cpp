#include "def.h"
#include "messages.h"
#include "sequences.h"

// config file https://www.walletfox.com/course/parseconfigfile.php#
// or https://github.com/brofield/simpleini
// or maybe just use env var...
const char *port = "57123";

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
    printf("quiting\n\n");
    fflush(stdout);

    return 0;
}

int main()
{
    lo_server_thread serverThread = lo_server_thread_new(port, error);

    printf("SuperSeq listening on port %s\n", port);

    lo_server server = lo_server_thread_get_server(serverThread);

    lo_server_thread_add_method(serverThread, "/seq", "iii", seq_handler, NULL);
    lo_server_thread_add_method(serverThread, "/msg", NULL, msg_handler, NULL);
    lo_server_thread_add_method(serverThread, "/msg_get", "i", msg_get_handler, server);
    lo_server_thread_add_method(serverThread, "/msg_arg", NULL, msg_arg_handler, NULL);
    lo_server_thread_add_method(serverThread, "/quit", "", quit_handler, NULL);

    lo_server_thread_start(serverThread);

    while (!done) {
#ifdef WIN32
        Sleep(1);
#else
        usleep(1000);
#endif
    }

    lo_server_thread_free(serverThread);

    return 0;
}
