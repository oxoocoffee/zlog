/*
 * This file is part of the zlog Library.
 *
 * Copyright (C) 2011 by Hardy Simpson <HardySimpson1984@gmail.com>
 *
 * Licensed under the LGPL v2.1, see the file COPYING in base directory.
 */

#include <stdio.h>
#include "test_level.h"

int main(int argc, char** argv)
{
	int rc;
	zlog_category_t *zc;

	rc = zlog_init("test_level.conf");
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

    zlog_set_verbosity_level(zc, ZLOG_LEVEL_DEBUG);

	zlog_msg(zc, "hello, zlog - msg");
	zlog_trace(zc, "hello, zlog - trace");
	zlog_debug(zc, "hello, zlog - debug");
	zlog_info(zc, "hello, zlog - info");
	zlog_monitor(zc, "hello, zlog - monitor");

	zlog_fini();
	
	return 0;
}
