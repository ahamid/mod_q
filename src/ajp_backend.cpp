#include "ajp_backend.h"
#include "Backend.h"

static DefaultBackend BACKEND;

START_EXTERN_C

int MODQ_ap_proxy_acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s) {
    return BACKEND.acquire_connection(proxy_function, conn, worker, s);
}

int MODQ_ap_proxy_release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s) {
    return BACKEND.release_connection(proxy_function, conn, s);
}

int MODQ_ap_proxy_determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                       apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size) {
    return BACKEND.determine_connection(p, r, conf, worker, conn, uri, url, proxyname, proxyport, server_portstr, server_portstr_size);
}

int MODQ_ap_proxy_connect_backend(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s) {
    return BACKEND.connect(proxy_function, conn, worker, s);
}

apr_status_t MODQ_ajp_send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri) {
    return BACKEND.send_header(ctx, r, buffsize, uri);
}

apr_status_t MODQ_ajp_handle_cping_cpong(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout) {
    return BACKEND.handle_cping_cpong(ctx, r, timeout);
}

/* new functions */

void MODQ_start_handling(backend_ctx * const conn) {
    return BACKEND.start_handling((proxy_conn_rec*) conn);
}

void MODQ_backend_close(backend_ctx * const conn) {
    BACKEND.backend_close(conn);
}

const char * MODQ_backend_hostname(const backend_ctx * const conn) {
    return BACKEND.backend_hostname(conn);
}

END_EXTERN_C
