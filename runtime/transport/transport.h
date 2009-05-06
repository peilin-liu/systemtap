#ifndef _TRANSPORT_TRANSPORT_H_ /* -*- linux-c -*- */
#define _TRANSPORT_TRANSPORT_H_

/** @file transport.h
 * @brief Header file for stp transport
 */

#include "transport_msgs.h"

/* The size of print buffers. This limits the maximum */
/* amount of data a print can send. */
#define STP_BUFFER_SIZE 8192

struct utt_trace;

static int _stp_ctl_write(int type, void *data, unsigned len);

static int _stp_transport_init(void);
static void _stp_transport_close(void);

static inline void *utt_reserve(struct utt_trace *utt, size_t length)
{
    return NULL;
}


/* STP_CTL_BUFFER_SIZE is the maximum size of a message */
/* exchanged on the control channel. */
#if STP_TRANSPORT_VERSION == 1
/* Old transport sends print output on control channel */
#define STP_CTL_BUFFER_SIZE STP_BUFFER_SIZE
#else
#define STP_CTL_BUFFER_SIZE 256
#endif

/* how often the work queue wakes up and checks buffers */
#define STP_WORK_TIMER (HZ/100)

static unsigned _stp_nsubbufs;
static unsigned _stp_subbuf_size;

static int _stp_transport_init(void);
static void _stp_transport_close(void);

static int _stp_lock_transport_dir(void);
static void _stp_unlock_transport_dir(void);

static struct dentry *_stp_get_root_dir(void);
static struct dentry *_stp_get_module_dir(void);

static int _stp_transport_fs_init(const char *module_name);
static void _stp_transport_fs_close(void);

static void _stp_attach(void);
static void _stp_detach(void);
static void _stp_handle_start(struct _stp_msg_start *st);

static uid_t _stp_uid;
static gid_t _stp_gid;

static int _stp_ctl_attached;

static int _stp_bufsize;

/*
 * All transports must provide the following functions.
 */

/*
 * _stp_transport_data_fs_init
 *
 * This function allocates any buffers needed, creates files,
 * etc. needed for this transport.
 */
static int _stp_transport_data_fs_init(void);

/* 
 * _stp_transport_data_fs_close
 *
 * This function cleans up items created by
 * _stp_transport_data_fs_init().
 */
static void _stp_transport_data_fs_close(void);

struct _stp_entry {
	void			*event;
	size_t			len;
	char			buf[];
};

/*
 * _stp_data_write_reserve - reserve bytes
 * size_request:	number of bytes to reserve
 * entry:		allocated buffer is returned here
 *
 * This function attempts to reserve size_request number of bytes,
 * returning the number of bytes actually reserved.  The allocated
 * buffer is returned in entry.  Note that the number of bytes
 * allocated may be less than the number of bytes requested.
 */
static size_t _stp_data_write_reserve(size_t size_request,
				      struct _stp_entry **entry);

/*
 * _stp_data_write_commit - 
 * entry:		_stp_entry returned by
 *			 _stp-data_write_reserve()
 *
 * This function notifies the transport that the bytes in entry are
 * ready to be written.  
 */
static int _stp_data_write_commit(struct _stp_entry *entry);

#endif /* _TRANSPORT_TRANSPORT_H_ */
