/*
 * This file is in the public domain.
 * You may freely use, modify, distribute, and relicense it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svndump.h"

static void print_usage() {
	fprintf(stderr, "svn-fe [--ref=dst_ref] [[--url=]url] < dump | fast-import-backend\n\n"
			"dst_ref - git ref to be updated with svn commits, defaults to refs/heads/master\n"
			"url - if set commit logs will have git-svn-id: line appended\n");
}

int main(int argc, char **argv)
{
	const char* url = NULL;
	const char* ref = "refs/heads/master";
	int i;
	for (i = 1; i < argc; ++i) {
		if (!strncmp(argv[i], "--url=", 6))
			url = argv[i] + 6;
		else if (!strncmp(argv[i], "--ref=", 6))
			ref = argv[i] + 6;
		else
			break;
	}
	if (i + 1 == argc && !url)
		url = argv[i++];
	if (i != argc) {
		print_usage();
		return 1;
	}
	if (svndump_init(NULL, ref))
		return 1;
	svndump_read(url);
	svndump_deinit();
	svndump_reset();
	return 0;
}
