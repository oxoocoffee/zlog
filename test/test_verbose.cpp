#include <iostream>
#include <signal.h>
#include <zlog.h>
#include <thread>
#include <chrono>

using namespace std;

zlog_category_t* ct;
bool             keepRunning = true;

void sigHandler(int sig)
{
    if( ct )
    {
        switch( sig )
        {
            case SIGINT:
                zlog_msg(ct, "SIGINT Intercepted");
                keepRunning = false;
                break;

            case SIGUSR1:
                zlog_set_verbosity_level(ct, ZLOG_LEVEL_DEBUG);
                zlog_msg(ct, "SIGUSR1 Intercepted -");
                break;

            case SIGUSR2:
                zlog_set_verbosity_level(ct, ZLOG_LEVEL_NOTICE);
                zlog_msg(ct, "SIGUSR2 Intercepted +");
                break;
        }
    }
}

void threadRunner(std::string msg)
{
    zlog_notice(ct, "Entered Thread: %s", msg.c_str());

    while(keepRunning)
    {
        this_thread::sleep_for(chrono::seconds(1));
        zlog_fatal(ct,  "\e[91m\e[1mFATAL\e[0m");           // Light Red Bold
        zlog_warn(ct,   "\e[93m\e[1mWARNING\e[0m");         // Light Yellow Bold
        zlog_notice(ct, "\e[92m\e[1mNOTICE\e[0m");          // Light Green Bold
        zlog_info(ct,   "\e[96m\e[1mINFO\e[0m");            // Light Cyan Bold
        zlog_debug(ct,  "\e[95m\e[1mDEBUG\e[0m");
    }

    zlog_notice(ct, "Exiting Thread: %s", msg.c_str());
}

int main()
{
    ct = 0L;

    int rc = zlog_init("/etc/zlog.conf");

    if (rc)
    {
        printf("zlog_init() failed\n");
        return -2;
    }

    ct = zlog_get_category("zlogTest");

    if (!ct)
    {
        printf("zlog_get_category(zlogTest) failed\n");
        zlog_fini();
        return -3;
    }

    zlog_notice(ct, "Registering Signals");

    //zlog_set_verbosity_level(ct, ZLOG_LEVEL_NOTICE);

    if( signal( SIGINT, sigHandler) == SIG_ERR )
        return -1;

    if( signal(SIGUSR1, sigHandler) == SIG_ERR )
        return -1;

    if( signal(SIGUSR2, sigHandler) == SIG_ERR )
        return -1;

    zlog_notice(ct, "Spawning Thread Runner");

    thread runner(threadRunner, "zlogTest");

    runner.join();

    zlog_notice(ct, "Exiting...");
    zlog_fini();

    return 0;
}

