FROM nginx:alpine

RUN apk update \
    && apk add openssl

RUN			openssl req -x509 -newkey rsa:2048 -nodes \
			-out /etc/ssl/certs/nginx.crt \
			-keyout /etc/ssl/private/nginx.key \
            -subj "/C=TR/ST=ISTANBUL/L=Istanbul/O=42Istanbul/CN=dayan.42.fr"

COPY ./default.conf /etc/nginx/conf.d/default.conf
