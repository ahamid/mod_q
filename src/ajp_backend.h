#ifndef AJP_BACKEND_H
#define AJP_BACKEND_H

#include "mod_q.h"
#include "ajp.h"
#include "mod_proxy.h"

START_EXTERN_C

typedef proxy_conn_rec backend_ctx;

int MODQ_ap_proxy_acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s);

int MODQ_ap_proxy_release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s);

int MODQ_ap_proxy_determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                       apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size);

int MODQ_ap_proxy_connect_backend(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s);

apr_status_t MODQ_ajp_send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri);

apr_status_t MODQ_ajp_handle_cping_cpong(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout);

END_EXTERN_C

#endif
