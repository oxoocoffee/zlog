/*
 * This file is part of the zlog Library.
 *
 * Copyright (C) 2011 by Hardy Simpson <HardySimpson1984@gmail.com>
 *
 * Licensed under the LGPL v2.1, see the file COPYING in base directory.
 */

#include <stdio.h>
#include <unistd.h>
#include "test_level.h"

int main(int argc, char** argv)
{
    int rc = zlog_init("test_level.conf");

	if (rc)
	{
		printf("init failed\n");
		return -1;
	}

    zlog_category_t *zc = zlog_get_category("clearwave");

	if (!zc)
	{
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

    //zlog_set_verbosity_level(zc, ZLOG_LEVEL_MONITOR);
    zlog_set_verbosity_level(zc, ZLOG_LEVEL_DEBUG);

    int i;

    for(i = 0; i < 1000; ++i)
    {
	    zlog_msg(zc,     "hello, zlog - %s %d", "MSG", i);
	    zlog_trace(zc,   "hello, zlog - %s %d", "TRACE", i);
	    zlog_debug(zc,   "hello, zlog - %s %d", "DEBUG", i);
	    zlog_info(zc,    "hello, zlog - %s %d", "INFO", i);
	    zlog_monitor(zc, "hello, zlog - %s %d", "MONITOR", i);
    }

    zlog_fini();

    sleep(5);	
	return 0;
}
