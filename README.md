# ddp-http

Kleines HTTP/1.1-Gerüst für [DDP – Die Deutsche Programmiersprache](https://github.com/DDP-Projekt/Kompilierer) (getestet mit v1.0.0): Anfrage vom Socket lesen (Kopf, `Content-Length`-Rumpf, Größenlimit, Zeitlimit), Antwort bauen und senden. Eine Verbindung nach der anderen, jede Antwort mit `Connection: close` – gedacht für kleine Dienste hinter einem Reverse-Proxy.

```
Binde "Duden/Netzwerk" ein.
Binde "lib/http/http" ein.

Bereite den HTTP-Dienst vor.
Der Socket sock ist ein TCP Socket.
Erlaube die Wiederverwendung der Adresse von sock.
Setze sock auf "0.0.0.0" 8080.
Lass sock auf maximal 16 Verbindungen warten.
Solange wahr, mache:
	Der Socket verbindung ist die nächste Verbindung auf sock.
	Setze das Zeitlimit von verbindung auf 5 Sekunden.
	Die Anfrage a ist die Anfrage aus verbindung mit höchstens 4096 Bytes.
	Wenn (fehler von a) gleich 0 ist, Antworte über verbindung mit 200, "text/plain; charset=utf-8" und "Hallo".
	Schließe verbindung.
```

Hinweise:
- Die DDP-Laufzeit braucht die Locale `de_DE.UTF-8` (sonst sind Nicht-ASCII-Zeichen kaputt).
- `netz.c` ergänzt, was `Duden/Netzwerk` in v1.0.0 fehlt: Socket-Zeitlimit (`SO_RCVTIMEO`/`SO_SNDTIMEO`), `SIGPIPE` ignorieren, zeilengepufferte Ausgabe, `SO_REUSEADDR` (`Erlaube die Wiederverwendung der Adresse von …`, direkt nach dem Anlegen des Sockets und vor `Setze sock auf …` aufrufen, sonst scheitert ein Neustart kurz nach Verbindungen an `bind`).
- Tests: `./test.sh` (braucht `kddp` im `PATH`).

Lizenz: MIT
