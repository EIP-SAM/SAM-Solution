#!/usr/bin/sh

openssl req -x509 -nodes -sha256 -days 365 -newkey rsa:4096 -keyout server.key -out server.crt
