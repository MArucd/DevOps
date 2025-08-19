FROM nginx

COPY ../nginx/nginx.conf ../etc/nginx/
COPY start.sh / 
COPY server.c /
 
RUN apt -y update && apt install -y gcc spawn-fcgi libfcgi-dev

CMD [ "/bin/bash", "start.sh" ]
