#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wow.h"
#include "rom.h"

static void compress(struct rom *rom, int start, int end)
{
	rom_dma_compress(rom, start, end, 1);
}

static void skip(struct rom *rom, int start, int end)
{
	rom_dma_compress(rom, start, end, 0);
}

static void repack(struct rom *rom, int start, int end)
{
	rom_dma_repack(
		rom
		, start
		, end
		, "yaz" /* old codec */
		, 0 /* new codec */
	);
}

static void do_pattern(
	struct rom *rom
	, const char *str
	, void func(struct rom *rom, int start, int end)
)
{
	const char *Ostr = str;
	int last_int = -1;
	int last_op = 0;
	int cur;
	int len;
	
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			++str;
			continue;
		}
		
		/* calculate length of current token */
		len = strspn(str, "0123456789xXaAbBcCdDeEfF"); /* allow hex */
		if (!len) /* no len, assume it's an operator */
			len = 1;
		
		/* is a number or variable */
		if (isdigit(*str) || !strncmp(str, "END", 3))
		{
			/* 'END' is shorthand for last entry */
			if (!strncmp(str, "END", 3))
			{
				cur = rom_dma_num(rom);
				str += 2;
			}
			
			/* otherwise, it's a number */
			else
				sscanf(str, "%i", &cur);
			
			if (cur < last_int)
				die(
					"invalid pattern '%s'; "
					"values are not in ascending order"
					, Ostr
				);
			
			/* apply operations on item(s) */
			if (last_op == '-')
				func(rom, last_int, cur);
			else
				func(rom, cur, cur);
			
			/* prevents processing this item
			 * again when 'through' is used
			 */
			cur += 1;
		}
		
		/* 'through' or 'single item', respectively */
		else if (*str == '-' || *str == ',')
		{
			if (last_int < 0)
				die(
					"invalid pattern '%s'; "
					"pattern does not begin with number"
					, Ostr
				);
			last_op = *str;
		}
		
		/* unknown character encountered */
		else
		{
			die(
				"invalid pattern '%s'; "
				"encountered unknown operator '%c'"
				, Ostr
				, *str
			);
		}
		
		/* advance */
		str += len;
		last_int = cur;
	}
}

static void usage(void)
{
	/* compression examples for users to adapt to their needs */
	fprintf(stderr, "\n");
	fprintf(stderr, "  compressing oot debug\n");
	fprintf(stderr, "    --in        \"path/to/in.z64\"\n");
	fprintf(stderr, "    --out       \"path/to/out.z64\"\n");
	fprintf(stderr, "    --mb        32\n");
	fprintf(stderr, "    --codec     yaz\n");
	fprintf(stderr, "    --cache     \"path/to/cache\"\n");
	fprintf(stderr, "    --dma       \"0x12F70,1548\"\n");
	fprintf(stderr, "    --compress  \"9-14,28-END\"\n");
	fprintf(stderr, "    --threads   4\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  compressing oot ntsc 1.0\n");
	fprintf(stderr, "    --in        \"path/to/in.z64\"\n");
	fprintf(stderr, "    --out       \"path/to/out.z64\"\n");
	fprintf(stderr, "    --mb        32\n");
	fprintf(stderr, "    --codec     yaz\n");
	fprintf(stderr, "    --cache     \"path/to/cache\"\n");
	fprintf(stderr, "    --dma       \"0x7430,1526\"\n");
	fprintf(stderr, "    --compress  \"10-14,27-END\"\n");
	fprintf(stderr, "    --threads   4\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  compressing mm usa\n");
	fprintf(stderr, "    --in        \"path/to/in.z64\"\n");
	fprintf(stderr, "    --out       \"path/to/out.z64\"\n");
	fprintf(stderr, "    --mb        32\n");
	fprintf(stderr, "    --codec     yaz\n");
	fprintf(stderr, "    --cache     \"path/to/cache\"\n");
	fprintf(stderr, "    --dma       \"0x1A500,1568\"\n");
	fprintf(stderr, "    --compress  \"10-14,23,24,31-END\"\n");
	fprintf(stderr, "    --skip      \"1127\"\n");
	fprintf(stderr, "    --repack    \"15-20,22\"\n");
	fprintf(stderr, "    --threads   4\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  arguments\n");
	fprintf(stderr, "    --in        uncompressed input rom\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --out       compressed output rom\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --mb        how many mb the compressed rom should be\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --codec     currently supported codecs\n");
	fprintf(stderr, "                   yaz\n");
	fprintf(stderr, "                   ucl\n");
	fprintf(stderr, "                   lzo\n");
	fprintf(stderr, "                   aplib\n");
	fprintf(stderr, "              * to use non-yaz codecs, find patches\n");
	fprintf(stderr, "                and code on my z64enc repo\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --cache     is optional and won't be created if\n");
	fprintf(stderr, "                no path is specified (having a cache\n");
	fprintf(stderr, "                makes subsequent compressions faster)\n");
	fprintf(stderr, "              * pro-tip: linux users who don't want a\n");
	fprintf(stderr, "                cache to persist across power cycles\n");
	fprintf(stderr, "                can use the path \"/tmp/z64compress\"\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --dma       specify dmadata address and count\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --compress  enable compression on specified files\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --skip      disable compression on specified files\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --repack    handles Majora's Mask archives\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "    --threads   optional multithreading;\n");
	fprintf(stderr, "                exclude this argument to disable it\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  arguments are executed as they\n");
	fprintf(stderr, "  are parsed, so order matters!\n");
	fprintf(stderr, "\n");
}

wow_main
{
	struct rom *rom = 0;
	const char *Ain = 0;
	const char *Aout = 0;
	const char *Adma = 0;
	const char *Acodec = 0;
	const char *Acache = 0;
	int Amb = 0;
	int Athreads = 0;
	wow_main_argv;
	
	fprintf(stderr, "welcome to z64compress <z64.me>\n");
	
	if (argc <= 1)
	{
		usage();
		return EXIT_FAILURE;
	}
	
	/* hacky argument handling  */
	for (int i = 1; i < argc; i += 2)
	{
		const char *arg = argv[i];
		const char *next = argv[i + 1];
		
		if (!next)
			die("%s missing parameter", arg);
		
		if (!strcmp(arg, "--in"))
		{
			if (Ain)
				die("--in arg provided more than once");
			Ain = next;
			rom = rom_new(Ain);
		}
		else if (!strcmp(arg, "--out"))
		{
			if (Aout)
				die("--out arg provided more than once");
			Aout = next;
		}
		else if (!strcmp(arg, "--cache"))
		{
			if (Acache)
				die("--cache arg provided more than once");
			Acache = next;
			rom_set_cache(rom, Acache);
		}
		else if (!strcmp(arg, "--codec"))
		{
			if (Acodec)
				die("--codec arg provided more than once");
			if (!Ain)
				die("--dma arg provided before --in arg");
			Acodec = next;
			rom_set_codec(rom, Acodec);
		}
		else if (!strcmp(arg, "--dma"))
		{
			int num;
			int start = 0;
			
			if (!Acodec)
				die("--dma arg provided before --codec arg");
			if (!Ain)
				die("--dma arg provided before --in arg");
			if (Adma)
				die("--dma arg provided more than once");
			Adma = next;
			if (sscanf(Adma, "%i,%i", &start, &num) != 2)
				die("--dma bad formatting '%s'", Adma);
			rom_dma(rom, start, num);
		}
		else if (!strcmp(arg, "--mb"))
		{
			if (Amb)
				die("--mb arg provided more than once");
			if (sscanf(next, "%i", &Amb) != 1)
				die("--mb could not get value from string '%s'", next);
			if (Amb <= 0)
				die("--mb invalid value %d", Amb);
		}
		else if (!strcmp(arg, "--compress"))
		{
			if (!Adma)
				die("--compress arg provided before --dma arg");
			do_pattern(rom, next, compress);
		}
		else if (!strcmp(arg, "--skip"))
		{
			if (!Adma)
				die("--skip arg provided before --dma arg");
			do_pattern(rom, next, skip);
		}
		else if (!strcmp(arg, "--repack"))
		{
			if (!Adma)
				die("--repack arg provided before --dma arg");
			if (!Acodec)
				die("--repack arg provided before --codec arg");
			do_pattern(rom, next, repack);
		}
		else if(!strcmp(arg, "--threads"))
		{
			if (Athreads)
				die("--threads arg provided more than once");
			if (sscanf(next, "%i", &Athreads) != 1)
				die("--threads could not get value from string '%s'", next);
			if (Athreads < 0)
				die("--threads invalid value %d", Athreads);
		}
		else
		{
			die("unknown argument '%s'", arg);
		}
	}
	
	#define ARG_ZERO_TEST(TEST, NAME) \
		if (!(TEST)) \
			die("no " NAME " arg provided")
	
	ARG_ZERO_TEST(Ain   , "--in"   );
	ARG_ZERO_TEST(Aout  , "--out"  );
	ARG_ZERO_TEST(Amb   , "--mb"   );
	ARG_ZERO_TEST(Acodec, "--codec");
	
	#undef ARG_ZERO_TEST
	
	/* finished initializing dma settings */
	rom_dma_ready(rom);
	
	/* compress rom */
	rom_compress(rom, Amb, Athreads);
	fprintf(stderr, "rom compressed successfully!\n");
	
	/* write compressed rom */
	rom_save(rom, Aout);
	fprintf(stderr, "compressed rom written successfully!\n");
	
	/* cleanup */
	rom_free(rom);
	
	return EXIT_SUCCESS;
}

