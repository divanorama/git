/*
 * This file is in the public domain.
 * You may freely use, modify, distribute, and relicense it.
 */

#include "git-compat-util.h"
#include "parse-options.h"
#include "svndump.h"

static const char * const svn_fe_usage[] = {
	"svn-fe [options] [git-svn-id-url] < dump | fast-import-backend",
	NULL
};

static const char *url;

static struct option svn_fe_options[] = {
	OPT_STRING(0, "git-svn-id-url", &url, "url",
		"if set commit messages will have git-svn-id: line appended"),
	OPT_END()
};

int main(int argc, const char **argv)
{
	argc = parse_options(argc, argv, NULL, svn_fe_options,
						svn_fe_usage, 0);
	if (argc == 1 && !url) {
		url = argv[0];
		--argc;
	}
	if (argc)
		usage_with_options(svn_fe_usage, svn_fe_options);
	if (svndump_init(NULL))
		return 1;
	svndump_read(url);
	svndump_deinit();
	svndump_reset();
	return 0;
}
