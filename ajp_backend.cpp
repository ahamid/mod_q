#include "ajp_backend.h"
#include "Backend.h"

static DefaultBackend DEFAULT_BACKEND;

START_EXTERN_C

int MODQ_ap_proxy_acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s) {
    return DEFAULT_BACKEND.acquire_connection(proxy_function, conn, worker, s);
}

int MODQ_ap_proxy_release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s) {
    return DEFAULT_BACKEND.release_connection(proxy_function, conn, s);
}

int MODQ_ap_proxy_determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                       apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size) {
    return DEFAULT_BACKEND.determine_connection(p, r, conf, worker, conn, uri, url, proxyname, proxyport, server_portstr, server_portstr_size);
}

int MODQ_ap_proxy_connect_backend(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s) {
    return DEFAULT_BACKEND.connect(proxy_function, conn, worker, s);
}

apr_status_t MODQ_ajp_send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri) {
    return DEFAULT_BACKEND.send_header(ctx, r, buffsize, uri);
}

apr_status_t MODQ_ajp_handle_cping_cpong(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout) {
    return DEFAULT_BACKEND.handle_cping_cpong(ctx, r, timeout);
}

END_EXTERN_C
