%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%This is simple client-server app %%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

CLient - client.c, asks you filename, and then send this file on local server
Server - Daemon_server.c, this is a daemon, that needed to start from console only one time, then it would be in process list constantly

In folder BIN there headers with needed functions

How to use:

1. Compile "Daemon_server.c"

Command: gcc Daemon_server.c BIN/*.c -std=c99 -o Daemon_server_main

2. Run Daemon_server_main 

3. Compile "client.c"

Command:   gcc client.c BIN/*.c -W -Wall -Werror -std=c99 -o client

4. Run client

5. Enter a filename, which data will be send

6. Check "log.txt" in folder with daemon for checking log info or check "server_*filename* to see the received data from client

7. To shutdown daemon use "kill -SIGHUP daemon_pid" or "kill -SIGTERM daemon_pid"





