/*
 * ProFTPD - FTP server daemon
 * Copyright (c) 2001, 2002 The ProFTPD Project team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * As a special exemption, The ProFTPD Project and other respective copyright
 * holders give permission to link this program with OpenSSL, and distribute
 * the resulting executable, without including the source code for OpenSSL in
 * the source distribution.
 */

/* Scoreboard routines.
 *
 * $Id: scoreboard.h,v 1.1 2002-09-25 23:43:19 castaglia Exp $
 */

#ifndef PR_SCOREBOARD_H
#define PR_SCOREBOARD_H

/* PR_SCOREBOARD_VERSION is used for checking for scoreboard compatibility
 */
#define PR_SCOREBOARD_VERSION        		0x01040000

/* Structure used as a header for scoreboard files.
 */
#define PR_SCOREBOARD_MAGIC			0xdeadbeef

typedef struct {

  /* Always 0xDEADBEEF */
  unsigned long sch_magic;

  /* Version of proftpd that created the scoreboard file */
  unsigned long sch_version;

  /* PID of the process to which this scoreboard belongs, or zero if inetd */
  pid_t sch_pid;

  /* Time when the daemon wrote this header */
  time_t sch_uptime;

} pr_scoreboard_header_t;

/* Structure used for writing scoreboard file entries.
 */

typedef struct {
  pid_t	sce_pid;
  uid_t sce_uid;
  gid_t sce_gid;
  char sce_user[80];
  p_in_addr_t *sce_server_ip;
  unsigned short sce_server_port;
  char sce_server_name[32], sce_addr[80];
  char sce_class[32];
  char sce_cwd[80];
  char sce_cmd[256];
  time_t sce_begin_idle, sce_begin_session;
  off_t sce_xfer_size, sce_xfer_done;

} pr_scoreboard_entry_t;

/* Scoreboard mode */
#define PR_SCOREBOARD_MODE		0644

/* Scoreboard update tags */
#define PR_SCORE_USER		1
#define PR_SCORE_ADDR		2
#define PR_SCORE_CLASS		3
#define PR_SCORE_CWD		4
#define PR_SCORE_CMD		5
#define PR_SCORE_SERVER_IP	6
#define PR_SCORE_SERVER_PORT	7
#define PR_SCORE_XFER_DONE	8
#define PR_SCORE_XFER_SIZE	9
#define PR_SCORE_BEGIN_IDLE	10
#define PR_SCORE_BEGIN_SESSION	11
#define PR_SCORE_SERVER_NAME	12

/* Scoreboard error values */
#define PR_SCORE_ERR_BAD_MAGIC		-2
#define PR_SCORE_ERR_OLDER_VERSION	-3
#define PR_SCORE_ERR_NEWER_VERSION	-4

const char *pr_get_scoreboard(void);
int pr_set_scoreboard(const char *);

int pr_close_scoreboard(void);
void pr_delete_scoreboard(void);
int pr_open_scoreboard(int, pid_t *);
int pr_restore_scoreboard(void);
int pr_rewind_scoreboard(void);

int pr_scoreboard_add_entry(void);
int pr_scoreboard_del_entry(void);
pr_scoreboard_entry_t *pr_scoreboard_read_entry(void);
int pr_scoreboard_update_entry(pid_t, ...);

#endif /* PR_SCOREBOARD_H */
