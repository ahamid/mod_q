#ifndef BACKEND_H
#define BACKEND_H

#include "mod_q.h"
START_EXTERN_C
#include "ajp.h"
#include "mod_proxy.h"
END_EXTERN_C

#include "ajp_backend.h"

class Backend {
public:
    virtual int acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s) = 0;
    virtual int release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s) = 0;

    virtual void start_handling(backend_ctx * const conn) = 0;
    virtual void backend_close(backend_ctx * const conn) = 0;
    virtual const char * backend_hostname(const backend_ctx * const conn) = 0;

    virtual int determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                     apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size) = 0;
    virtual int connect(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s) = 0;
    virtual apr_status_t send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri) = 0;
    virtual apr_status_t handle_cping_cpong(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout) = 0;
};

class DefaultBackend : public Backend {
public:
    virtual int acquire_connection(const char *proxy_function, backend_ctx **conn, proxy_worker *worker, server_rec *s);

    virtual void start_handling(backend_ctx * const conn);
    virtual void backend_close(backend_ctx * const conn);
    virtual const char * backend_hostname(const backend_ctx * const conn);

    virtual int release_connection(const char *proxy_function, backend_ctx *conn, server_rec *s);
    virtual int determine_connection(apr_pool_t *p, request_rec *r, proxy_server_conf *conf, proxy_worker *worker, backend_ctx *conn,
                                     apr_uri_t *uri, char **url, const char *proxyname, apr_port_t proxyport, char *server_portstr, int server_portstr_size);
    virtual int connect(const char *proxy_function, backend_ctx *conn, proxy_worker *worker, server_rec *s);
    virtual apr_status_t send_header(backend_ctx *ctx, request_rec *r, apr_size_t buffsize, apr_uri_t *uri);
    virtual apr_status_t handle_cping_cpong(backend_ctx *ctx, request_rec *r, apr_interval_time_t timeout);
private:
    proxy_conn_rec* conn;
};

#endif
