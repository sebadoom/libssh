/*
 * knownhosts.c
 * This file contains an example of how verify the identity of a
 * SSH server using libssh
 */

/*
Copyright 2003-2009 Aris Adamantiadis

This file is part of the SSH Library

You are free to copy this file, modify it in any way, consider it being public
domain. This does not apply to the rest of the library though, but it is
allowed to cut-and-paste working code from this file to any license of
program.
The goal is to show the API in action. It's not a reference on how terminal
clients must be made or how a client should react.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <libssh/libssh.h>
#include "examples_common.h"

int verify_knownhost(ssh_session session){
  char *hexa;
  int state;
  char buf[10];
  unsigned char *hash = NULL;
  int hlen;

  state=ssh_is_server_known(session);

  hlen = ssh_get_pubkey_hash(session, &hash);
  if (hlen < 0) {
    ssh_disconnect(session);
    ssh_finalize();
    return 1;
  }
  switch(state){
    case SSH_SERVER_KNOWN_OK:
      break; /* ok */
    case SSH_SERVER_KNOWN_CHANGED:
      fprintf(stderr,"Host key for server changed : server's one is now :\n");
      ssh_print_hexa("Public key hash",hash, hlen);
      free(hash);
      fprintf(stderr,"For security reason, connection will be stopped\n");
      ssh_disconnect(session);
      ssh_finalize();
      exit(-1);
    case SSH_SERVER_FOUND_OTHER:
      fprintf(stderr,"The host key for this server was not found but an other type of key exists.\n");
      fprintf(stderr,"An attacker might change the default server key to confuse your client"
          "into thinking the key does not exist\n"
          "We advise you to rerun the client with -d or -r for more safety.\n");
      ssh_disconnect(session);
      ssh_finalize();
      exit(-1);
    case SSH_SERVER_FILE_NOT_FOUND:
      fprintf(stderr,"Could not find known host file. If you accept the host key here,\n");
      fprintf(stderr,"the file will be automatically created.\n");
      /* fallback to SSH_SERVER_NOT_KNOWN behavior */
    case SSH_SERVER_NOT_KNOWN:
      hexa = ssh_get_hexa(hash, hlen);
      fprintf(stderr,"The server is unknown. Do you trust the host key ?\n");
      fprintf(stderr, "Public key hash: %s\n", hexa);
      free(hexa);
      fgets(buf,sizeof(buf),stdin);
      if(strncasecmp(buf,"yes",3)!=0){
        ssh_disconnect(session);
        exit(-1);
      }
      fprintf(stderr,"This new key will be written on disk for further usage. do you agree ?\n");
      fgets(buf,sizeof(buf),stdin);
      if(strncasecmp(buf,"yes",3)==0){
        if (ssh_write_knownhost(session) < 0) {
          free(hash);
          fprintf(stderr, "error %s\n", strerror(errno));
          exit(-1);
        }
      }

      break;
    case SSH_SERVER_ERROR:
      free(hash);
      fprintf(stderr,"%s",ssh_get_error(session));
      ssh_disconnect(session);
      ssh_finalize();
      exit(-1);
  }
  free(hash);
  return 0;
}
