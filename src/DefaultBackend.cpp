#ifndef DEFAULTBACKEND_H
#define DEFAULTBACKEND_H

#include "Backend.h"


int DefaultBackend::acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s) {
    return ap_proxy_acquire_connection(proxy_function, conn, worker, s);
}

int DefaultBackend::release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s) {
    return ap_proxy_release_connection(proxy_function, conn, s);
}

int DefaultBackend::determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                        apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size) {
    return ap_proxy_determine_connection(p, r, conf, worker, conn, uri, url, proxyname, proxyport, server_portstr, server_portstr_size);
}

int DefaultBackend::connect(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s) {
    return ap_proxy_connect_backend(proxy_function, conn, worker, s);
}

apr_status_t DefaultBackend::send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri) {
    return ajp_send_header(ctx->sock, r, buffsize, uri);
}

apr_status_t DefaultBackend::handle_cping_cpong(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout) {
    return ajp_handle_cping_cpong(ctx->sock, r, timeout);
}


#endif
