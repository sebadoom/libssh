/*
 * This file is part of the SSH Library
 *
 * Copyright (c) 2010 by Aris Adamantiadis
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

/** functions in that file are wrappers to the newly named functions. All
 * of them are depreciated, but these wrapper will avoid breaking backward
 * compatibility
 */

#include "config.h"

#include <libssh/priv.h>
#include <libssh/session.h>
#include <libssh/server.h>
#include <libssh/buffer.h>
#include <libssh/pki.h>
#include "libssh/pki_priv.h"
#include <libssh/keys.h>
#include <libssh/keyfiles.h>

/* AUTH FUNCTIONS */
int ssh_auth_list(ssh_session session) {
  return ssh_userauth_list(session, NULL);
}

int ssh_userauth_offer_pubkey(ssh_session session, const char *username,
    int type, ssh_string publickey)
{
    ssh_key key;
    int rc;

    (void) type; /* unused */

    rc = ssh_pki_import_pubkey_blob(publickey, &key);
    if (rc < 0) {
        ssh_set_error(session, SSH_FATAL, "Failed to convert public key");
        return SSH_AUTH_ERROR;
    }

    rc = ssh_userauth_try_publickey(session, username, key);
    ssh_key_free(key);

    return rc;
}

/* BUFFER FUNCTIONS */

void buffer_free(ssh_buffer buffer){
  ssh_buffer_free(buffer);
}
void *buffer_get(ssh_buffer buffer){
  return ssh_buffer_get_begin(buffer);
}
uint32_t buffer_get_len(ssh_buffer buffer){
  return ssh_buffer_get_len(buffer);
}
ssh_buffer buffer_new(void){
  return ssh_buffer_new();
}

ssh_channel channel_accept_x11(ssh_channel channel, int timeout_ms){
  return ssh_channel_accept_x11(channel, timeout_ms);
}

int channel_change_pty_size(ssh_channel channel,int cols,int rows){
  return ssh_channel_change_pty_size(channel,cols,rows);
}

ssh_channel channel_forward_accept(ssh_session session, int timeout_ms){
  return ssh_forward_accept(session,timeout_ms);
}

int channel_close(ssh_channel channel){
  return ssh_channel_close(channel);
}

int channel_forward_cancel(ssh_session session, const char *address, int port){
  return ssh_forward_cancel(session, address, port);
}

int channel_forward_listen(ssh_session session, const char *address,
    int port, int *bound_port){
  return ssh_forward_listen(session, address, port, bound_port);
}

void channel_free(ssh_channel channel){
  ssh_channel_free(channel);
}

int channel_get_exit_status(ssh_channel channel){
  return ssh_channel_get_exit_status(channel);
}

ssh_session channel_get_session(ssh_channel channel){
  return ssh_channel_get_session(channel);
}

int channel_is_closed(ssh_channel channel){
  return ssh_channel_is_closed(channel);
}

int channel_is_eof(ssh_channel channel){
  return ssh_channel_is_eof(channel);
}

int channel_is_open(ssh_channel channel){
  return ssh_channel_is_open(channel);
}

ssh_channel channel_new(ssh_session session){
  return ssh_channel_new(session);
}

int channel_open_forward(ssh_channel channel, const char *remotehost,
    int remoteport, const char *sourcehost, int localport){
  return ssh_channel_open_forward(channel, remotehost, remoteport,
      sourcehost,localport);
}

int channel_open_session(ssh_channel channel){
  return ssh_channel_open_session(channel);
}

int channel_poll(ssh_channel channel, int is_stderr){
  return ssh_channel_poll(channel, is_stderr);
}

int channel_read(ssh_channel channel, void *dest, uint32_t count, int is_stderr){
  return ssh_channel_read(channel, dest, count, is_stderr);
}

/*
 * This function will completely be depreciated. The old implementation was not
 * renamed.
 * int channel_read_buffer(ssh_channel channel, ssh_buffer buffer, uint32_t count,
 *   int is_stderr);
 */

int channel_read_nonblocking(ssh_channel channel, void *dest, uint32_t count,
    int is_stderr){
  return ssh_channel_read_nonblocking(channel, dest, count, is_stderr);
}

int channel_request_env(ssh_channel channel, const char *name, const char *value){
  return ssh_channel_request_env(channel, name, value);
}

int channel_request_exec(ssh_channel channel, const char *cmd){
  return ssh_channel_request_exec(channel, cmd);
}

int channel_request_pty(ssh_channel channel){
  return ssh_channel_request_pty(channel);
}

int channel_request_pty_size(ssh_channel channel, const char *term,
    int cols, int rows){
  return ssh_channel_request_pty_size(channel, term, cols, rows);
}

int channel_request_shell(ssh_channel channel){
  return ssh_channel_request_shell(channel);
}

int channel_request_send_signal(ssh_channel channel, const char *signum){
  return ssh_channel_request_send_signal(channel, signum);
}

int channel_request_sftp(ssh_channel channel){
  return ssh_channel_request_sftp(channel);
}

int channel_request_subsystem(ssh_channel channel, const char *subsystem){
  return ssh_channel_request_subsystem(channel, subsystem);
}

int channel_request_x11(ssh_channel channel, int single_connection, const char *protocol,
    const char *cookie, int screen_number){
  return ssh_channel_request_x11(channel, single_connection, protocol, cookie,
      screen_number);
}

int channel_send_eof(ssh_channel channel){
  return ssh_channel_send_eof(channel);
}

int channel_select(ssh_channel *readchans, ssh_channel *writechans, ssh_channel *exceptchans, struct
    timeval * timeout){
  return ssh_channel_select(readchans, writechans, exceptchans, timeout);
}

void channel_set_blocking(ssh_channel channel, int blocking){
  ssh_channel_set_blocking(channel, blocking);
}

int channel_write(ssh_channel channel, const void *data, uint32_t len){
  return ssh_channel_write(channel, data, len);
}

/*
 * These functions have to be wrapped around the pki.c functions.

void privatekey_free(ssh_private_key prv);
ssh_private_key privatekey_from_file(ssh_session session, const char *filename,
    int type, const char *passphrase);
void publickey_free(ssh_public_key key);
int ssh_publickey_to_file(ssh_session session, const char *file,
    ssh_string pubkey, int type);
ssh_public_key publickey_from_privatekey(ssh_private_key prv);
ssh_string publickey_to_string(ssh_public_key key);
 *
 */

void string_burn(ssh_string str){
  ssh_string_burn(str);
}

ssh_string string_copy(ssh_string str){
  return ssh_string_copy(str);
}

void *string_data(ssh_string str){
  return ssh_string_data(str);
}

int string_fill(ssh_string str, const void *data, size_t len){
  return ssh_string_fill(str,data,len);
}

void string_free(ssh_string str){
  ssh_string_free(str);
}

ssh_string string_from_char(const char *what){
  return ssh_string_from_char(what);
}

size_t string_len(ssh_string str){
  return ssh_string_len(str);
}

ssh_string string_new(size_t size){
  return ssh_string_new(size);
}

char *string_to_char(ssh_string str){
  return ssh_string_to_char(str);
}

ssh_private_key privatekey_from_base64(ssh_session session,
                                       const char *b64_pkey,
                                       int type,
                                       const char *passphrase) {
    ssh_auth_callback auth_fn = NULL;
    void *auth_data = NULL;
    ssh_private_key privkey;
    ssh_key key;

    (void) type; /* unused */

    if (session->common.callbacks) {
        auth_fn = session->common.callbacks->auth_function;
        auth_data = session->common.callbacks->userdata;
    }

    key = pki_private_key_from_base64(b64_pkey, passphrase, auth_fn, auth_data);
    if (key == NULL) {
        return NULL;
    }

    privkey = malloc(sizeof(struct ssh_private_key_struct));
    if (privkey == NULL) {
        ssh_key_free(key);
        return NULL;
    }

    privkey->type = key->type;
    privkey->dsa_priv = key->dsa;
    privkey->rsa_priv = key->rsa;

    return privkey;
}

ssh_private_key privatekey_from_file(ssh_session session,
                                     const char *filename,
                                     int type,
                                     const char *passphrase) {
    ssh_auth_callback auth_fn = NULL;
    void *auth_data = NULL;
    ssh_private_key privkey;
    ssh_key key;
    int rc;

    (void) type; /* unused */

    if (session->common.callbacks) {
        auth_fn = session->common.callbacks->auth_function;
        auth_data = session->common.callbacks->userdata;
    }


    rc = ssh_pki_import_privkey_file(filename,
                                     passphrase,
                                     auth_fn,
                                     auth_data,
                                     &key);
    if (rc == SSH_ERROR) {
        return NULL;
    }

    privkey = malloc(sizeof(struct ssh_private_key_struct));
    if (privkey == NULL) {
        ssh_key_free(key);
        return NULL;
    }

    privkey->type = key->type;
    privkey->dsa_priv = key->dsa;
    privkey->rsa_priv = key->rsa;

    key->dsa = NULL;
    key->rsa = NULL;

    ssh_key_free(key);

    return privkey;
}

ssh_private_key _privatekey_from_file(void *session, const char *filename,
    int type) {
    return privatekey_from_file(session, filename, type, NULL);
}

enum ssh_keytypes_e ssh_privatekey_type(ssh_private_key privatekey){
  if (privatekey==NULL)
    return SSH_KEYTYPE_UNKNOWN;
  return privatekey->type;
}

void privatekey_free(ssh_private_key prv) {
  if (prv == NULL) {
    return;
  }

#ifdef HAVE_LIBGCRYPT
  gcry_sexp_release(prv->dsa_priv);
  gcry_sexp_release(prv->rsa_priv);
#elif defined HAVE_LIBCRYPTO
  DSA_free(prv->dsa_priv);
  RSA_free(prv->rsa_priv);
#endif
  memset(prv, 0, sizeof(struct ssh_private_key_struct));
  SAFE_FREE(prv);
}

ssh_string publickey_from_file(ssh_session session, const char *filename,
    int *type) {
    ssh_key key;
    ssh_string key_str;
    int rc;

    (void) session; /* unused */

    rc = ssh_pki_import_pubkey_file(filename, &key);
    if (rc < 0) {
        return NULL;
    }

    key_str = ssh_pki_export_pubkey_blob(key);
    if (key_str == NULL) {
        return NULL;
    }

    *type = key->type;
    ssh_key_free(key);

    return key_str;
}

const char *ssh_type_to_char(int type) {
    return ssh_key_type_to_char(type);
}

int ssh_type_from_name(const char *name) {
    return ssh_key_type_from_name(name);
}

ssh_public_key publickey_from_string(ssh_session session, ssh_string pubkey_s) {
    struct ssh_public_key_struct *pubkey;
    ssh_key key;
    int rc;

    (void) session; /* unused */

    rc = ssh_pki_import_pubkey_blob(pubkey_s, &key);
    if (rc < 0) {
        return NULL;
    }

    pubkey = malloc(sizeof(struct ssh_public_key_struct));
    if (pubkey == NULL) {
        ssh_key_free(key);
        return NULL;
    }

    pubkey->type = key->type;
    pubkey->type_c = key->type_c;

    pubkey->dsa_pub = key->dsa;
    key->dsa = NULL;
    pubkey->rsa_pub = key->rsa;
    key->rsa = NULL;

    ssh_key_free(key);

    return pubkey;
}

ssh_string publickey_to_string(ssh_public_key pubkey) {
    ssh_key key;
    ssh_string key_blob;

    key = ssh_key_new();
    if (key == NULL) {
        return NULL;
    }

    key->type = pubkey->type;
    key->type_c = pubkey->type_c;

    key->dsa = pubkey->dsa_pub;
    key->rsa = pubkey->rsa_pub;

    key_blob = ssh_pki_export_pubkey_blob(key);

    key->dsa = NULL;
    key->rsa = NULL;
    ssh_key_free(key);

    return key_blob;
}

ssh_string signature_to_string(SIGNATURE *sign)
{
    ssh_signature sig;
    ssh_string sig_blob;
    int rc;

    if (sign == NULL) {
        return NULL;
    }

    sig = ssh_signature_new();
    if (sig == NULL) {
        return NULL;
    }

    sig->type = sign->type;
    sig->dsa_sig = sign->dsa_sign;
    sig->rsa_sig = sign->rsa_sign;

    rc = ssh_pki_export_signature_blob(sig, &sig_blob);
    sig->dsa_sig = NULL;
    sig->rsa_sig = NULL;
    ssh_signature_free(sig);
    if (rc < 0) {
        return NULL;
    }

    return sig_blob;
}

SIGNATURE *signature_from_string(ssh_session session,
                                 ssh_string signature,
                                 ssh_public_key pubkey,
                                 int needed_type)
{
    SIGNATURE *sign;
    ssh_signature sig;
    ssh_key key;
    int rc;

    if (session == NULL || signature == NULL || pubkey == NULL) {
        return NULL;
    }

    key = ssh_key_new();
    if (key == NULL) {
        return NULL;
    }

    key->type = pubkey->type;
    key->type_c = pubkey->type_c;
    key->flags = SSH_KEY_FLAG_PUBLIC;
    key->dsa = pubkey->dsa_pub;
    key->rsa = pubkey->rsa_pub;

    rc = ssh_pki_import_signature_blob(signature, key, &sig);
    key->dsa = NULL;
    key->rsa = NULL;
    ssh_key_free(key);
    if (rc < 0) {
        return NULL;
    }

    if ((enum ssh_keytypes_e)needed_type != sig->type) {
        ssh_signature_free(sig);
        return NULL;
    }

    sign = malloc(sizeof(struct signature_struct));
    if (sign == NULL) {
        ssh_signature_free(sig);
        return NULL;
    }

    sign->type = sig->type;
    sign->dsa_sign = sig->dsa_sig;
    sig->dsa_sig = NULL;
    sign->rsa_sign = sig->rsa_sig;
    sig->rsa_sig = NULL;

    ssh_signature_free(sig);
    return sign;
}

/****************************************************************************
 * SERVER SUPPORT
 ****************************************************************************/

#ifdef WITH_SERVER
int ssh_accept(ssh_session session) {
    return ssh_handle_key_exchange(session);
}

int channel_write_stderr(ssh_channel channel, const void *data, uint32_t len) {
    return ssh_channel_write(channel, data, len);
}

/** @deprecated
 * @brief Interface previously exported by error.
 */
ssh_message ssh_message_retrieve(ssh_session session, uint32_t packettype){
	(void) packettype;
	ssh_set_error(session, SSH_FATAL, "ssh_message_retrieve: obsolete libssh call");
	return NULL;
}

#endif /* WITH_SERVER */
