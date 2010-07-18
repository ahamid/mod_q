#ifndef DEFAULTBACKEND_H
#define DEFAULTBACKEND_H

#include "Backend.h"


int DefaultBackend::acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s) {
    return ap_proxy_acquire_connection(proxy_function, (proxy_conn_rec**) conn, worker, s);
}

int DefaultBackend::release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s) {
    proxy_conn_rec* pcr = (proxy_conn_rec*) conn;
    pcr->close_on_recycle = 1;
    return ap_proxy_release_connection(proxy_function, pcr, s);
}

int DefaultBackend::determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                        apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size) {
    return ap_proxy_determine_connection(p, r, conf, worker, (proxy_conn_rec*) conn, uri, url, proxyname, proxyport, server_portstr, server_portstr_size);
}

int DefaultBackend::connect(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s) {
    return ap_proxy_connect_backend(proxy_function, (proxy_conn_rec*) conn, worker, s);
}

apr_status_t DefaultBackend::send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri) {
    return ajp_send_header(((proxy_conn_rec*) ctx)->sock, r, buffsize, uri);
}

apr_status_t DefaultBackend::renew_handshake(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout) {
    proxy_conn_rec* rec = (proxy_conn_rec*) ctx;
    return ajp_handle_cping_cpong(((proxy_conn_rec*)ctx)->sock, r, timeout);
}

/* new functions */


void DefaultBackend::start_handling(backend_ctx* const conn) {
    proxy_conn_rec* const pcr = (proxy_conn_rec*) conn;
    pcr->is_ssl = 0;
    pcr->close_on_recycle = 0;
}

void DefaultBackend::backend_close(backend_ctx* const conn) {
    proxy_conn_rec* const pcr = (proxy_conn_rec*) conn;
    pcr->close++;
}

const char * DefaultBackend::backend_hostname(const backend_ctx* const conn) {
    const proxy_conn_rec* const pcr = (proxy_conn_rec*) conn;
    return pcr->hostname;
}

#endif
