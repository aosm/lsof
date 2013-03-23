/*
 * dlsof.h - AIX header file for lsof
 */


/*
 * Copyright 1994 Purdue Research Foundation, West Lafayette, Indiana
 * 47907.  All rights reserved.
 *
 * Written by Victor A. Abell
 *
 * This software is not subject to any license of the American Telephone
 * and Telegraph Company or the Regents of the University of California.
 *
 * Permission is granted to anyone to use this software for any purpose on
 * any computer system, and to alter it and redistribute it freely, subject
 * to the following restrictions:
 *
 * 1. Neither the authors nor Purdue University are responsible for any
 *    consequences of the use of this software.
 *
 * 2. The origin of this software must not be misrepresented, either by
 *    explicit claim or by omission.  Credit to the authors and Purdue
 *    University must appear in documentation and sources.
 *
 * 3. Altered versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 4. This notice may not be removed or altered.
 */


/*
 * $Id: dlsof.h,v 1.25 2001/08/14 12:27:01 abe Exp $
 */


#if	!defined(AIX_LSOF_H)
#define	AIX_LSOF_H	1

# if	AIXA>=1
/*
 * !!!WARNING!!!     !!!WARNING!!!   !!!WARNING!!!   !!!WARNING!!!
 *
 * The following two ugly ia64 AIX 5L hacks prevent the inclusion of
 * <jfs/ino.h> and <jfs/inode.h> by the chain that begins with the innocent
 * inclusion of <procinfo.h>.  The JFS file system is deprecated in ia64 AIX
 * 5L and no header file in /usr/include should include header files from
 * /usr/include/jfs, but as of AIX 5L Beta 3, <sys/inode.h> still did.
 *
 * !!!WARNING!!!     !!!WARNING!!!   !!!WARNING!!!   !!!WARNING!!!
*/
#define	_H_JFS_INO	/* !!! WARNING!!! */
#define	_H_JFS_INODE	/* !!! WARNING!!! */

#include <nlist.h>
# endif	/* AIXA>=1 */

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <setjmp.h>
#include <unistd.h>

# if	!defined(_KERNEL)
#define _KERNEL	1
# endif	/* !defined(_KERNEL) */

#include <sys/vnode.h>
#include <sys/file.h>
#include <procinfo.h>		/* <procinfo.h> #includes <sys/user.h> */
#define p_pid	pi_pid
#define	p_pgid	pi_pgrp
#define	p_ppid	pi_ppid

# if	AIXV<4300
#define p_stat	pi_stat
# else	/* AIXV>=4300 */
#define	p_stat	pi_state
# endif	/* AIXV<4300 */

#define p_uid	pi_uid
#undef	sleep
#undef	_KERNEL

# if	AIXA>=1
#define	_NET_NET_MALLOC		/* to keep <sys/mbuf.h> from #include'ing
				 * <sys/ppda.h>, which is missing from
				 * ia64 AIX 5L */
# endif	/* AIXA>=1 */

#include <sys/mbuf.h>
#include <sys/mntctl.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>

# if	AIXV>=4140
#include <sys/stream.h>
# endif	/* AIXV>=4140 */

#include <sys/sysmacros.h>
#include <sys/un.h>
#include <sys/unpcb.h>

# if	AIXA>=1
#include <j2/j2_inode.h>
# endif	/* AIXA>=1 */

#include <netinet/in.h>
#include <net/route.h>
#include <net/raw_cb.h>

# if	AIXV>=4100
#include <netinet/ip.h>
# endif	/* AIXV>=4100 */

#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcpip.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <sys/vattr.h>
#include <sys/statfs.h>

#include <rpc/rpc.h>
#include <rpc/pmap_prot.h>

# if	defined(HAS_AFS)
#define	__XDR_INCLUDE__
# endif	/* defined(HAS_AFS) */

#include <sys/vfs.h>
#include <sys/vmount.h>

# if	AIXV>=4100
#  if	AIXV>=4110
#undef	u
#undef	u_comm
#undef	u_cdir
#undef	u_rdir
#undef	u_maxofile
#undef	u_ufd
#undef	u_loader
#  endif	/* AIXV>=4110 */

#define	u_comm		U_comm
#define	u_cdir		U_cdir
#define	u_rdir		U_rdir
#define	u_maxofile	U_maxofile
#define	u_ufd		U_ufd
#define	u_loader	U_loader
# endif	/* AIXV>=4100 */

#  if	AIXV>=3200
#include <sys/specnode.h>
#  endif	/* AIXV>=3200 */

/*
 * AIX doesn't supply cdrnode.h.
 */

struct cdrnode {
	caddr_t		f1[4];
	struct gnode	f2;
	dev_t		f3;
	ino_t		cn_inumber;	/* inode number */
	caddr_t		f4;
	cnt_t		f5[2];
	u_short		f6;
	uint		f7[2];
	uchar		f8[3];
	off_t		cn_size;	/* size of file in bytes */
};

# if	defined(HAS_AFS)

/*
 *  Avoid typdef conflicts in <afs/stds.h>.
 */

#  if	defined(HASINT16TYPE)
#define	int16	AFS_int16
#  endif	/* defined(HASINT16TYPE */
#  if	defined(HASUINT16TYPE)
#define	u_int16	AFS_u_int16
#  endif	/* defined(HASUINT16TYPE */
#  if	defined(HASINT32TYPE)
#define int32	AFS_int32
#  endif	/* defined(HASINT32TYPE) */

#include <afs/stds.h>
#include <afs/param.h>
#include <afs/afsint.h>
#include <afs/vldbint.h>
# endif	/* defined(HAS_AFS) */


/*
 * Miscellaneous definitions.
 */

# if	defined(HAS_AFS)
#define	AFSAPATHDEF	"/usr/vice/etc/dkload/???"
#define	AFSDEV		1	/* AFS "fake" device number */

#  if	!defined(MNT_AFS)
#define	MNT_AFS		AFS_MOUNT_AFS
#  endif	/* !defined(MNT_AFS) */
# endif	/* defined(HAS_AFS) */

#define	COMP_P		const void
#define DEVINCR		1024	/* device table malloc() increment */

# if	AIXV<4200
typedef	off_t		KA_T;
# else	/* AIXV>=4200 */
#  if	AIXA<1
typedef	unsigned int	KA_T;
#  else	/* AIXA>=1 */
typedef u_longlong_t	KA_T;
#define	GET_MAJ_DEV	major64
#define	GET_MIN_DEV	minor64
#define	KA_T_FMT_X	"%#llx"
#  endif	/* AIXA<1 */
# endif	/* AIXV<4200 */

#define KMEM		"/dev/kmem"

# if	defined(HASSTAT64)
#define	lstat		lstat64
#define	stat		stat64
# endif	/* defined(HASSTAT64) */

#define MALLOC_P	char
#define FREE_P		MALLOC_P
#define MALLOC_S	size_t
#define	N_UNIX		"/unix"
#define QSORT_P		void
#define	READLEN_T	size_t
#define STRNCPY_L	size_t

# if	AIXV>=4200
#define	SZOFFTYPE	unsigned long long
				/* size and offset type definition */
#define	SZOFFPSPEC	"ll"	/* SZOFFTYPE print specification modifier */
# endif	/* AIXV>=4200 */

#define U_SIZE		sizeof(struct user)


/*
 * Name list (Nl[]) indexes
 */

#define	X_UADDR		0
#define	X_NL_NUM	1


/*
 * Definition for ckfa.c
 */

#define	CKFA_MPXCHAN	1


/*
 * Definitions for dvch.c
 */

# if	AIXV>=4140
#define	DCACHE_CLONE	rw_clone_sect	/* clone function for read_dcache */
#define	DCACHE_CLR	clr_sect	/* function to clear clone and
					 * pseudo caches when reading the
					 * device cache file fails */
# endif	/* AIXV>=4140 */


/*
 * Definitions for enter_dir()
 */

#define	DIRTYPE	dirent
#define	HASDNAMLEN	1


# if	defined(HAS_AFS)
/*
 * AFS name list (AFSnl[]) indexes
 */

#define	X_AFS_FID	0
#define	X_AFS_VOL	1
#define	X_AFSNL_NUM	2
# endif	/* defined(HAS_AFS) */


# if	AIXV>=4140
/*
 * Local clone information
 */

struct clone {
	struct l_dev cd;		/* device, inode, name, verify status */
	struct clone *next;		/* next entry */
};
extern struct clone *Clone;
extern int CloneMaj;
extern int ClonePtc;
#endif	/* AIXV>=4140 */


/*
 * Local vfs information
 */

struct l_vfs {
	KA_T addr;			/* kernel address */
	dev_t dev;			/* device */
	char *dir;			/* mounted directory */
	char *fsname;			/* file system name */
	int vmt_flags;			/* vmount flags */
	int vmt_gfstype;		/* vmount gfs type */
	struct l_vfs *next;		/* forward link */
};
extern struct l_vfs *Lvfs;


/*
 * Local mount information
 */

struct mounts {
        char *dir;              	/* directory (mounted on) */
	char *fsname;           	/* file system
					 * (symbolic links unresolved) */
	char *fsnmres;           	/* file system
					 * (symbolic links resolved) */
        dev_t dev;              	/* directory st_dev */
	dev_t rdev;			/* directory st_rdev */
	ino_t inode;			/* directory st_ino */
	u_short mode;			/* directory st_mode */
	u_short fs_mode;		/* file system st_mode */

# if	defined(HASFSTYPE)
	int fstype;			/* fs type */
# endif	/* defined(HASFSTYPE) */

        struct mounts *next;    	/* forward link */
};
extern struct mounts *Mtab;


/*
 * Search file information
 */

struct sfile {
	char *aname;			/* file name argument */
	char *name;			/* file name (after readlink()) */
	char *devnm;			/* device name (optional) */
	dev_t dev;			/* device */
	dev_t rdev;			/* raw device */
	chan_t ch;			/* channel (last path component,
					 * (if numeric) */
	u_short mode;			/* S_IFMT mode bits from stat() */
	int type;			/* file type: 0 = file system
				 	 *	      1 = regular file */
	ino_t i;			/* inode number */
	int f;				/* file found flag */
	struct sfile *next;		/* forward link */
};


/*
 * Miscellaneous external definitions
 */

# if	defined(HAS_AFS)
extern struct nlist AFSnl[];	/* AFS kernel symbol name list table */

#  if	defined(HASAOPT)
extern char *AFSApath;		/* alternate AFS name list path (from -a) */
#  endif	/* defined(HASAOPT) */

extern KA_T AFSVfsp;		/* AFS struct vfs kernel pointer */
# endif	/* defined(HAS_AFS) */

extern int Kd;
extern int Km;
extern struct nlist Nl[];

# if	defined(TCPSTATES) && AIXV<=3250
/*
 * For AIX 3.2.5 and below, there is no header file with the  definition
 * of tcpstates[], needed by ptti.c's print_tcptpi() function.
 */

static char *tcpstates[] = {
	"CLOSED",       "LISTEN",       "SYN_SENT",     "SYN_RCVD",
	"ESTABLISHED",  "CLOSE_WAIT",   "FIN_WAIT_1",   "CLOSING",
	"LAST_ACK",     "FIN_WAIT_2",   "TIME_WAIT"
};
# endif	/* defined(TCPSTATES) && AIXV<=3250 */


# if	AIXA>=1
/*
 * This AIX 5L or above ia64 (aka Monterey) hack prevents the loader from
 * linking lsof's kread() in preference to the kread() that read() uses.
 * The very existence of a system kread() is an unwarrranted invasion of
 * user name space!
 */

#define	kread	lsof_kread		/* avoid conflict with the kread()
					 * in libc.so */
# endif	/* AIXA>=1 */

#endif	/* AIX_LSOF_H */
