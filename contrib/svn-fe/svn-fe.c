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
		"add git-svn-id line to log messages, imitating git-svn"),
	OPT_END()
};

int main(int argc, const char **argv)
{
	argc = parse_options(argc, argv, NULL, svn_fe_options,
						svn_fe_usage, 0);
	if (argc > 1)
		usage_with_options(svn_fe_usage, svn_fe_options);

	if (argc == 1) {
		if (url)
			usage_msg_opt("git-svn-id-url is set twice: as a "
					"--parameter and as a [parameter]",
					svn_fe_usage, svn_fe_options);
		url = argv[0];
	}
	if (svndump_init(NULL))
		return 1;
	svndump_read(url);
	svndump_deinit();
	svndump_reset();
	return 0;
}
