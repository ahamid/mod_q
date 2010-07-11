#!/bin/sh
exec httpd -X -f $(cd $(dirname $0); pwd)/httpd/conf/httpd.conf
