/*
 * This file is part of the SSH Library
 *
 * Copyright (c) 2009 by Aris Adamantiadis
 *
 * The SSH Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * The SSH Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the SSH Library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef POLL_H_
#define POLL_H_

/* poll.c */
int ssh_poll(ssh_pollfd_t *fds, nfds_t nfds, int timeout);
typedef struct ssh_poll_ctx SSH_POLL_CTX;
typedef struct ssh_poll SSH_POLL;

/**
 * @brief SSH poll callback.
 *
 * @param p             Poll object this callback belongs to.
 * @param fd            The raw socket.
 * @param revents       The current poll events on the socket.
 * @param userdata      Userdata to be passed to the callback function.
 *
 * @return              0 on success, < 0 if you removed the poll object from
 *                      it's poll context.
 */
typedef int (*ssh_poll_callback)(SSH_POLL *p, int fd, int revents,
    void *userdata);


SSH_POLL *ssh_poll_new(socket_t fd, short events, ssh_poll_callback cb,
    void *userdata);
void ssh_poll_free(SSH_POLL *p);
SSH_POLL_CTX *ssh_poll_get_ctx(SSH_POLL *p);
short ssh_poll_get_events(SSH_POLL *p);
void ssh_poll_set_events(SSH_POLL *p, short events);
void ssh_poll_add_events(SSH_POLL *p, short events);
void ssh_poll_remove_events(SSH_POLL *p, short events);
socket_t ssh_poll_get_fd(SSH_POLL *p);
void ssh_poll_set_callback(SSH_POLL *p, ssh_poll_callback cb, void *userdata);
SSH_POLL_CTX *ssh_poll_ctx_new(size_t chunk_size);
void ssh_poll_ctx_free(SSH_POLL_CTX *ctx);
int ssh_poll_ctx_add(SSH_POLL_CTX *ctx, SSH_POLL *p);
void ssh_poll_ctx_remove(SSH_POLL_CTX *ctx, SSH_POLL *p);
int ssh_poll_ctx(SSH_POLL_CTX *ctx, int timeout);

#endif /* POLL_H_ */