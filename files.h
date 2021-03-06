/*
 * maintain .fss file in monitored direcotory, header file
 *
 * Copyright (c) 2010, 2011 lxd <edl.eppc@gmail.com>
 * 
 * This file is part of File Synchronization System(fss).
 *
 * fss is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, 
 * (at your option) any later version.
 *
 * fss is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fss.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FSS_FILES_H_
#define _FSS_FILES_H_

#include "fss.h"

#define PREFIX0_SENT 0
#define PREFIX1_SENT 2
#define PREFIX2_SENT 3
#define PREFIX3_SENT 4

#define DIFF_BOTH_UNIQ 0
#define DIFF_IDENTICAL 2
#define DIFF_LOCAL_UNIQ 3
#define DIFF_REMOTE_UNIQ 4


#define FINFO_FSS "finfo.fss"

#define HASH_FSS "hash.fss"
#define TEMP_HASH_FSS "temp.hash.fss"

/* remote.hash.fss is ONLY server's sha.fss @ client */
#define REMOTE_HASH_FSS "remote.hash.fss"

/* remote.hash.fss's unique hash record line_number in remote.hash.fss */
#define DIFF_REMOTE_INDEX "diff.remote.index.fss"

/* local's hash.fss's unique hash record line_number in hash.fss */
#define DIFF_LOCAL_INDEX "diff.local.index.fss"

#define DEL_INDEX "del.index.fss"

int set_rootpath(const char *root_path);
int update_files();
int generate_diffs();

/* send.... */
int send_del_index_info(int sockfd, const char *prefix);

int send_del_index(int sockfd);
int send_file_via_linenum(int sockfd);
int send_file(int sockfd, const char *relaname);

int send_entryinfo_via_linenum(int sockfd, long linenum,
			       const char *prefix0, const char *prefix1);
int send_entryinfo(int sockfd, const char *fname,
		   const char *prefix0,  const char *prefix1);

int send_msg(int sockfd, const char *msg);


/* TODO:
 *     this 3 functions are a little bit noisy, should be rewriete */
//client
int send_linenum_or_done(int sockfd, int ifinit,
			 const char *prefix0, const char *prefix1);

int send_entryinfo_or_reqhashinfo(int sockfd, int ifinit,
				  const char *prefix0,
				  const char *prefix1, const char *prefix2);

/* receive... */
int receive_hash_fss(int sockfd, off_t sz);
int receive_common_file(int sockfd, const char *rela_fname, off_t sz);
int receive_file(int sockfd, const char *relaname, off_t size);

int create_dir(const char *relafname);
int remove_dir(const char *fname);


time_t hash_fss_mtime();
int remove_diffs();
int remove_files();

#endif
