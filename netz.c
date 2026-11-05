/* ddp-http: Hilfen aus C, die Duden/Netzwerk (v1.0.0) fehlen. MIT-Lizenz. */
#include "DDP/ddptypes.h"
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>

/* Abgebrochene Verbindungen dürfen den Prozess nicht beenden (send() ohne MSG_NOSIGNAL);
   stdout zeilenweise, damit Logs in Containern sofort erscheinen. */
void Http_Vorbereiten(void) {
	signal(SIGPIPE, SIG_IGN);
	setvbuf(stdout, NULL, _IOLBF, 0);
}

/* DDP übergibt Kombinationen als Zeiger; erstes Feld von Socket ist der Deskriptor. */
void Http_Zeitlimit(const int *sock, ddpint sekunden) {
	struct timeval tv = { .tv_sec = (time_t)sekunden, .tv_usec = 0 };
	setsockopt(sock[0], SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
	setsockopt(sock[0], SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
}
