#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include <string>
#include <iostream>

#define VERSION_H                        \
"/* AUTO GENERATED FILE */\n"		 \
"\n"                                     \
"#pragma once\n"                 	 \
"\n"                                     \
"#define %s_VERSION_MAJOR %d\n"          \
"#define %s_VERSION_MINOR %d\n"          \
"#define %s_VERSION_PATCH %d\n"          \
"#define %s_VERSION_BUILD %d\n"          \
"#define %s_VERSION_META \"%s\"\n"       \
"#define %s_VERSION \"%d.%d.%d.%d%s\"\n" \
"#define %s_COMPILE_DATE \"%s\"\n"       \
"#define %s_COMPILE_TIME \"%s\"\n"       \
"\n"

#define USAGE                                                                  \
"Usage: %s [-hMmpbaPDTiB]\n"                                                   \
"\n"                                                                           \
"Options:\n"                                                                   \
"  -h, --help        Print this menu and exit.\n"                              \
"  -M, --major       Major number.\n"                                          \
"  -m, --minor       Minor number.\n"                                          \
"  -p, --patch       Patch number.\n"                                          \
"  -b, --build       Build number.\n"                                          \
"  -a, --meta        Meta information.\n"                                      \
"  -P, --prefix      The macro prefix [default: \"%s\"]\n"                     \
"  -D, --date        Date format [default: \"%s\"]\n"                          \
"  -T, --time        Time format [default: \"%s\"]\n"                          \
"  -i, --auto-build  Auto increment build number.\n"                           \
"  -F, --build-file  The file containing the build number.\n"                  \
"\n"

int main(int argc, char **argv)
{
	struct option long_options[] = {
		{"help",       required_argument, NULL, 'h'},
		{"major",      required_argument, NULL, 'M'},
		{"minor",      required_argument, NULL, 'm'},
		{"patch",      required_argument, NULL, 'p'},
		{"build",      required_argument, NULL, 'b'},
		{"meta",       required_argument, NULL, 'a'},
		{"prefix",     required_argument, NULL, 'P'},
		{"date",       required_argument, NULL, 'D'},
		{"time",       required_argument, NULL, 'T'},
		{"auto-build",       no_argument, NULL, 'i'},
		{"build-file", required_argument, NULL, 'F'},
	};
	int major, minor, patch, build, c, auto_inc_build;
	std::string meta, prefix, datefmt, timefmt, buildfile;
	time_t timer;
	struct tm *tm_info;
	char datestr[32];
	char timestr[32];

	memset(datestr, 0, sizeof(datestr));
	memset(timestr, 0, sizeof(timestr));

	major = minor = patch = build = auto_inc_build = 0;
	meta = "";
	prefix = "FRAMEWORK";
	datefmt = "%Y-%m-%d";
	timefmt = "%H:%M:%S";
	buildfile = "";

	while ((c = getopt_long(argc, argv, "hM:m:p:b:a:P:D:T:iF:",
		long_options, 0)) != -1) {
		switch (c) {
		case 'h':
			printf(USAGE, argv[0], prefix, datefmt, timefmt);
			return 0;
		case 'M':
			major = atoi(optarg);
			break;
		case 'm':
			minor = atoi(optarg);
			break;
		case 'p':
			patch = atoi(optarg);
			break;
		case 'b':
			build = atoi(optarg);
			break;
		case 'a':
			meta = std::string( optarg ) ;
			break;
		case 'P':
			prefix = std::string( optarg );
			break;
		case 'D':
			datefmt = std::string( optarg );
			break;
		case 'T':
			timefmt = std::string( optarg );
			break;
		case 'i':
			auto_inc_build = 1;
			break;
		case 'F':
			buildfile = std::string( optarg );
			break;
		case '?':
			exit(1);
		}
	}

	if (auto_inc_build) {
		if ( buildfile.compare("") != 0 ) 
		{

			/* 65535 builds should be plenty (plus null-terminator) */
			char line[17];
			FILE *fp = fopen( buildfile.c_str() , "r");
			if (fp == NULL) {
				/* Don't overwrite build number if we can't
				 * open file; keep the existing value. */
				build = build != 0 ? build : 0;
			} else {
				fread(line, sizeof(line), 1, fp);
				build = atoi(line);
				fclose(fp);
			}

			build++;
			/* Reopen to write new value; Truncate file. */
			fp = fopen( buildfile.c_str() , "w+");
			if (fp == NULL) {
				fprintf(stderr, "%s: %s\n", buildfile.c_str(), strerror(errno));
				exit(1);
			}
			/* Overwrite existing build value. */
			snprintf(line, sizeof(line), "%d", build);
			fprintf(fp, "%d", build);
			fclose(fp);

		}
	}

	time(&timer);
	tm_info = localtime(&timer);

	strftime(datestr, sizeof(datestr), datefmt.c_str(), tm_info);
	strftime(timestr, sizeof(timestr), timefmt.c_str(), tm_info);

	printf(VERSION_H,
		prefix.c_str(), major,
		prefix.c_str(), minor,
		prefix.c_str(), patch,
		prefix.c_str(), build,
		prefix.c_str(), meta.c_str(),
		prefix.c_str(), major, minor, patch, build, meta.c_str(),
		prefix.c_str(), datestr,
		prefix.c_str(), timestr);

	return 0;
}
