// Copyright (C) 2017 The Qt Company Ltd.
// Copyright (C) 2014 BlackBerry Limited. All rights reserved.


/****************************************************************************
**
** In addition, as a special exception, the copyright holders listed above give
** permission to link the code of its release of Qt with the OpenSSL project's
** "OpenSSL" library (or modified versions of the "OpenSSL" library that use the
** same license as the original version), and distribute the linked executables.
**
** You must comply with the GNU General Public License version 2 in all
** respects for all of the code used other than the "OpenSSL" code.  If you
** modify this file, you may extend this exception to your version of the file,
** but you are not obligated to do so.  If you do not wish to do so, delete
** this exception statement from your version of this file.
**
****************************************************************************/

#ifndef QSSLSOCKET_OPENSSL_SYMBOLS_P_H
#define QSSLSOCKET_OPENSSL_SYMBOLS_P_H


//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtNetwork/private/qtnetworkglobal_p.h>

#include "qopenssl_p.h"

#include <QtCore/qglobal.h>

#if QT_CONFIG(ocsp)
#include <QtNetwork/private/qocsp_p.h>
#endif

QT_BEGIN_NAMESPACE

#define DUMMYARG

#if !defined QT_LINKED_OPENSSL
// **************** Shared declarations ******************
// ret func(arg)

#  define DEFINEFUNC(ret, func, arg, a, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg); \
    static _q_PTR_##func _q_##func = nullptr; \
    ret q_##func(arg) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func); \
            err; \
        } \
        funcret _q_##func(a); \
    }

// ret func(arg1, arg2)
#  define DEFINEFUNC2(ret, func, arg1, a, arg2, b, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2);         \
    static _q_PTR_##func _q_##func = nullptr;         \
    ret q_##func(arg1, arg2) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func);\
            err; \
        } \
        funcret _q_##func(a, b); \
    }

// ret func(arg1, arg2, arg3)
#  define DEFINEFUNC3(ret, func, arg1, a, arg2, b, arg3, c, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2, arg3);            \
    static _q_PTR_##func _q_##func = nullptr;                  \
    ret q_##func(arg1, arg2, arg3) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func); \
            err; \
        } \
        funcret _q_##func(a, b, c); \
    }

// ret func(arg1, arg2, arg3, arg4)
#  define DEFINEFUNC4(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2, arg3, arg4);               \
    static _q_PTR_##func _q_##func = nullptr;                           \
    ret q_##func(arg1, arg2, arg3, arg4) { \
         if (Q_UNLIKELY(!_q_##func)) { \
             qsslSocketUnresolvedSymbolWarning(#func); \
             err; \
         } \
         funcret _q_##func(a, b, c, d); \
    }

// ret func(arg1, arg2, arg3, arg4, arg5)
#  define DEFINEFUNC5(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2, arg3, arg4, arg5);         \
    static _q_PTR_##func _q_##func = nullptr;                           \
    ret q_##func(arg1, arg2, arg3, arg4, arg5) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func); \
            err; \
        } \
        funcret _q_##func(a, b, c, d, e); \
    }

// ret func(arg1, arg2, arg3, arg4, arg6)
#  define DEFINEFUNC6(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, arg6, f, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2, arg3, arg4, arg5, arg6);   \
    static _q_PTR_##func _q_##func = nullptr;                           \
    ret q_##func(arg1, arg2, arg3, arg4, arg5, arg6) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func); \
            err; \
        } \
        funcret _q_##func(a, b, c, d, e, f); \
    }

// ret func(arg1, arg2, arg3, arg4, arg6, arg7)
#  define DEFINEFUNC7(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, arg6, f, arg7, g, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);   \
    static _q_PTR_##func _q_##func = nullptr;                                 \
    ret q_##func(arg1, arg2, arg3, arg4, arg5, arg6, arg7) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func); \
            err; \
        } \
        funcret _q_##func(a, b, c, d, e, f, g); \
    }

// ret func(arg1, arg2, arg3, arg4, arg6, arg7, arg8, arg9)
#  define DEFINEFUNC9(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, arg6, f, arg7, g, arg8, h, arg9, i, err, funcret) \
    typedef ret (*_q_PTR_##func)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);   \
    static _q_PTR_##func _q_##func = nullptr;                                             \
    ret q_##func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) { \
        if (Q_UNLIKELY(!_q_##func)) { \
            qsslSocketUnresolvedSymbolWarning(#func); \
            err; \
        }   \
        funcret _q_##func(a, b, c, d, e, f, g, h, i); \
    }
// **************** Shared declarations ******************

#else // !defined QT_LINKED_OPENSSL

// **************** Static declarations ******************

// ret func(arg)
#  define DEFINEFUNC(ret, func, arg, a, err, funcret) \
    ret q_##func(arg) { funcret func(a); }

// ret func(arg1, arg2)
#  define DEFINEFUNC2(ret, func, arg1, a, arg2, b, err, funcret) \
    ret q_##func(arg1, arg2) { funcret func(a, b); }

// ret func(arg1, arg2, arg3)
#  define DEFINEFUNC3(ret, func, arg1, a, arg2, b, arg3, c, err, funcret) \
    ret q_##func(arg1, arg2, arg3) { funcret func(a, b, c); }

// ret func(arg1, arg2, arg3, arg4)
#  define DEFINEFUNC4(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, err, funcret) \
    ret q_##func(arg1, arg2, arg3, arg4) { funcret func(a, b, c, d); }

// ret func(arg1, arg2, arg3, arg4, arg5)
#  define DEFINEFUNC5(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, err, funcret) \
    ret q_##func(arg1, arg2, arg3, arg4, arg5) { funcret func(a, b, c, d, e); }

// ret func(arg1, arg2, arg3, arg4, arg6)
#  define DEFINEFUNC6(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, arg6, f, err, funcret) \
    ret q_##func(arg1, arg2, arg3, arg4, arg5, arg6) { funcret func(a, b, c, d, e, f); }

// ret func(arg1, arg2, arg3, arg4, arg6, arg7)
#  define DEFINEFUNC7(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, arg6, f, arg7, g, err, funcret) \
    ret q_##func(arg1, arg2, arg3, arg4, arg5, arg6, arg7) { funcret func(a, b, c, d, e, f, g); }

// ret func(arg1, arg2, arg3, arg4, arg6, arg7, arg8, arg9)
#  define DEFINEFUNC9(ret, func, arg1, a, arg2, b, arg3, c, arg4, d, arg5, e, arg6, f, arg7, g, arg8, h, arg9, i, err, funcret) \
    ret q_##func(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) { funcret func(a, b, c, d, e, f, g, h, i); }

// **************** Static declarations ******************

#endif // !defined QT_LINKED_OPENSSL
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
typedef uint64_t qssloptions;
#else
typedef unsigned long qssloptions;
#endif
// TODO: the following lines previously were a part of 1.1 - specific header.
// To reduce the amount of the change, I'm directly copying and pasting the
// content of the header here. Later, can be better sorted/split into groups,
// depending on the functionality.

const unsigned char * q_ASN1_STRING_get0_data(const ASN1_STRING *x);

BIO *q_BIO_new(const BIO_METHOD *a);
const BIO_METHOD *q_BIO_s_mem();

void q_AUTHORITY_INFO_ACCESS_free(AUTHORITY_INFO_ACCESS *a);
int q_EVP_CIPHER_CTX_reset(EVP_CIPHER_CTX *c);
int q_EVP_PKEY_up_ref(EVP_PKEY *a);
EVP_PKEY_CTX *q_EVP_PKEY_CTX_new(EVP_PKEY *pkey, ENGINE *e);
void q_EVP_PKEY_CTX_free(EVP_PKEY_CTX *ctx);
int q_EVP_PKEY_param_check(EVP_PKEY_CTX *ctx);
int q_OPENSSL_sk_num(OPENSSL_STACK *a);
void q_OPENSSL_sk_pop_free(OPENSSL_STACK *a, void (*b)(void *));
OPENSSL_STACK *q_OPENSSL_sk_new_null();
void q_OPENSSL_sk_push(OPENSSL_STACK *st, void *data);
void q_OPENSSL_sk_free(OPENSSL_STACK *a);
void * q_OPENSSL_sk_value(OPENSSL_STACK *a, int b);
int q_SSL_session_reused(SSL *a);
qssloptions q_SSL_CTX_set_options(SSL_CTX *ctx, qssloptions op);
int q_OPENSSL_init_ssl(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings);
size_t q_SSL_get_client_random(SSL *a, unsigned char *out, size_t outlen);
size_t q_SSL_SESSION_get_master_key(const SSL_SESSION *session, unsigned char *out, size_t outlen);
int q_CRYPTO_get_ex_new_index(int class_index, long argl, void *argp, CRYPTO_EX_new *new_func, CRYPTO_EX_dup *dup_func, CRYPTO_EX_free *free_func);
const SSL_METHOD *q_TLS_method();
const SSL_METHOD *q_TLS_client_method();
const SSL_METHOD *q_TLS_server_method();
ASN1_TIME *q_X509_getm_notBefore(X509 *a);
ASN1_TIME *q_X509_getm_notAfter(X509 *a);
void q_ASN1_item_free(ASN1_VALUE *val, const ASN1_ITEM *it);
void q_X509V3_conf_free(CONF_VALUE *val);

void q_X509_up_ref(X509 *a);
long q_X509_get_version(X509 *a);
EVP_PKEY *q_X509_get_pubkey(X509 *a);
void q_X509_STORE_set_verify_cb(X509_STORE *ctx, X509_STORE_CTX_verify_cb verify_cb);
int q_X509_STORE_set_ex_data(X509_STORE *ctx, int idx, void *data);
void *q_X509_STORE_get_ex_data(X509_STORE *r, int idx);
STACK_OF(X509) *q_X509_STORE_CTX_get0_chain(X509_STORE_CTX *ctx);

# define q_SSL_load_error_strings() q_OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS \
                                                       | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL)

#define q_SKM_sk_num(st) q_OPENSSL_sk_num((OPENSSL_STACK *)st)
#define q_SKM_sk_value(type, st,i) (type *)q_OPENSSL_sk_value((OPENSSL_STACK *)st, i)

#define q_OPENSSL_add_all_algorithms_conf()  q_OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_CIPHERS \
                                                                   | OPENSSL_INIT_ADD_ALL_DIGESTS \
                                                                   | OPENSSL_INIT_LOAD_CONFIG, NULL)
#define  q_OPENSSL_add_all_algorithms_noconf() q_OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_CIPHERS \
                                                                    | OPENSSL_INIT_ADD_ALL_DIGESTS, NULL)

int q_OPENSSL_init_crypto(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings);

long q_OpenSSL_version_num();
const char *q_OpenSSL_version(int type);

unsigned long q_SSL_SESSION_get_ticket_lifetime_hint(const SSL_SESSION *session);
unsigned long q_SSL_set_options(SSL *s, unsigned long op);

#ifdef TLS1_3_VERSION
int q_SSL_CTX_set_ciphersuites(SSL_CTX *ctx, const char *str);

// The functions below do not really have to be ifdefed like this, but for now
// they only used in TLS 1.3 handshake (and probably future versions).
// Plus, 'is resumalbe' is OpenSSL 1.1.1-only (and again we need it for
// TLS 1.3-specific session management).

extern "C"
{
using NewSessionCallback = int (*)(SSL *, SSL_SESSION *);
}

void q_SSL_CTX_sess_set_new_cb(SSL_CTX *ctx, NewSessionCallback cb);
int q_SSL_SESSION_is_resumable(const SSL_SESSION *s);

#define q_SSL_CTX_set_session_cache_mode(ctx,m) \
    q_SSL_CTX_ctrl(ctx,SSL_CTRL_SET_SESS_CACHE_MODE,m,NULL)

#endif

#if QT_CONFIG(dtls)
// Functions and types required for DTLS support:
extern "C"
{

typedef int (*CookieVerifyCallback)(SSL *, const unsigned char *, unsigned);
typedef int (*DgramWriteCallback) (BIO *, const char *, int);
typedef int (*DgramReadCallback) (BIO *, char *, int);
typedef int (*DgramPutsCallback) (BIO *, const char *);
typedef long (*DgramCtrlCallback) (BIO *, int, long, void *);
typedef int (*DgramCreateCallback) (BIO *);
typedef int (*DgramDestroyCallback) (BIO *);

}

int q_DTLSv1_listen(SSL *s, BIO_ADDR *client);
BIO_ADDR *q_BIO_ADDR_new();
void q_BIO_ADDR_free(BIO_ADDR *ap);

// API we need for a custom dgram BIO:

BIO_METHOD *q_BIO_meth_new(int type, const char *name);
void q_BIO_meth_free(BIO_METHOD *biom);
int q_BIO_meth_set_write(BIO_METHOD *biom, DgramWriteCallback);
int q_BIO_meth_set_read(BIO_METHOD *biom, DgramReadCallback);
int q_BIO_meth_set_puts(BIO_METHOD *biom, DgramPutsCallback);
int q_BIO_meth_set_ctrl(BIO_METHOD *biom, DgramCtrlCallback);
int q_BIO_meth_set_create(BIO_METHOD *biom, DgramCreateCallback);
int q_BIO_meth_set_destroy(BIO_METHOD *biom, DgramDestroyCallback);

#endif // dtls

void q_BIO_set_data(BIO *a, void *ptr);
void *q_BIO_get_data(BIO *a);
void q_BIO_set_init(BIO *a, int init);
int q_BIO_get_shutdown(BIO *a);
void q_BIO_set_shutdown(BIO *a, int shut);

#if QT_CONFIG(ocsp)
const OCSP_CERTID *q_OCSP_SINGLERESP_get0_id(const OCSP_SINGLERESP *x);
#endif // ocsp

#define q_SSL_CTX_set_min_proto_version(ctx, version) \
        q_SSL_CTX_ctrl(ctx, SSL_CTRL_SET_MIN_PROTO_VERSION, version, nullptr)

#define q_SSL_CTX_set_max_proto_version(ctx, version) \
        q_SSL_CTX_ctrl(ctx, SSL_CTRL_SET_MAX_PROTO_VERSION, version, nullptr)

extern "C" {
typedef int (*q_SSL_psk_use_session_cb_func_t)(SSL *, const EVP_MD *, const unsigned char **, size_t *,
                                               SSL_SESSION **);
}
void q_SSL_set_psk_use_session_callback(SSL *s, q_SSL_psk_use_session_cb_func_t);
// Here the content of the 1.1 header ends.

bool q_resolveOpenSslSymbols();
long q_ASN1_INTEGER_get(ASN1_INTEGER *a);
int q_ASN1_INTEGER_cmp(const ASN1_INTEGER *x, const ASN1_INTEGER *y);
int q_ASN1_STRING_length(ASN1_STRING *a);
int q_ASN1_STRING_to_UTF8(unsigned char **a, ASN1_STRING *b);
int q_ASN1_TIME_to_tm(const ASN1_TIME *s, struct tm *tm);
long q_BIO_ctrl(BIO *a, int b, long c, void *d);
int q_BIO_free(BIO *a);
BIO *q_BIO_new_mem_buf(void *a, int b);
int q_BIO_read(BIO *a, void *b, int c);
int q_BIO_write(BIO *a, const void *b, int c);
int q_BN_num_bits(const BIGNUM *a);
int q_BN_is_word(BIGNUM *a, BN_ULONG w);
BN_ULONG q_BN_mod_word(const BIGNUM *a, BN_ULONG w);

X509 *q_d2i_X509(X509 **a, const unsigned char **b, long c);
char *q_ERR_error_string(unsigned long a, char *b);
void q_ERR_error_string_n(unsigned long e, char *buf, size_t len);
unsigned long q_ERR_get_error();
EVP_CIPHER_CTX *q_EVP_CIPHER_CTX_new();
void q_EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *a);
int q_EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX *ctx, int type, int arg, void *ptr);
int q_EVP_CIPHER_CTX_set_key_length(EVP_CIPHER_CTX *x, int keylen);
int q_EVP_CipherInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, const unsigned char *key, const unsigned char *iv, int enc);
int q_EVP_CipherInit_ex(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, ENGINE *impl, const unsigned char *key, const unsigned char *iv, int enc);
int q_EVP_CipherUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in, int inl);
int q_EVP_CipherFinal(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl);
const EVP_MD *q_EVP_get_digestbyname(const char *name);

#ifndef OPENSSL_NO_DES
const EVP_CIPHER *q_EVP_des_cbc();
const EVP_CIPHER *q_EVP_des_ede3_cbc();
#endif // OPENSSL_NO_DES

#ifndef OPENSSL_NO_RC2
const EVP_CIPHER *q_EVP_rc2_cbc();
#endif // OPENSSL_NO_RC2

#ifndef OPENSSL_NO_AES
const EVP_CIPHER *q_EVP_aes_128_cbc();
const EVP_CIPHER *q_EVP_aes_192_cbc();
const EVP_CIPHER *q_EVP_aes_256_cbc();
#endif // OPENSSL_NO_AES

const EVP_MD *q_EVP_sha1();

void q_EVP_PKEY_free(EVP_PKEY *a);
int q_EVP_PKEY_type(int a);
EVP_PKEY *q_EVP_PKEY_new();
int q_i2d_X509(X509 *a, unsigned char **b);
const char *q_OBJ_nid2sn(int a);
const char *q_OBJ_nid2ln(int a);
int q_OBJ_sn2nid(const char *s);
int q_OBJ_ln2nid(const char *s);
int q_i2t_ASN1_OBJECT(char *buf, int buf_len, ASN1_OBJECT *obj);
int q_OBJ_obj2txt(char *buf, int buf_len, ASN1_OBJECT *obj, int no_name);
int q_OBJ_obj2nid(const ASN1_OBJECT *a);
#define q_EVP_get_digestbynid(a) q_EVP_get_digestbyname(q_OBJ_nid2sn(a))
EVP_PKEY *q_PEM_read_bio_PrivateKey(BIO *a, EVP_PKEY **b, pem_password_cb *c, void *d);

int q_PEM_write_bio_PrivateKey(BIO *a, EVP_PKEY *b, const EVP_CIPHER *c, unsigned char *d,
                               int e, pem_password_cb *f, void *g);
int q_PEM_write_bio_PrivateKey_traditional(BIO *a, EVP_PKEY *b, const EVP_CIPHER *c, unsigned char *d,
                               int e, pem_password_cb *f, void *g);
EVP_PKEY *q_PEM_read_bio_PUBKEY(BIO *a, EVP_PKEY **b, pem_password_cb *c, void *d);
int q_PEM_write_bio_PUBKEY(BIO *a, EVP_PKEY *b);

void q_RAND_seed(const void *a, int b);
int q_RAND_status();
int q_RAND_bytes(unsigned char *b, int n);
int q_SSL_accept(SSL *a);
int q_SSL_clear(SSL *a);
char *q_SSL_CIPHER_description(const SSL_CIPHER *a, char *b, int c);
int q_SSL_CIPHER_get_bits(const SSL_CIPHER *a, int *b);
BIO *q_SSL_get_rbio(const SSL *s);
int q_SSL_connect(SSL *a);
int q_SSL_CTX_check_private_key(const SSL_CTX *a);
long q_SSL_CTX_ctrl(SSL_CTX *a, int b, long c, void *d);
void q_SSL_CTX_free(SSL_CTX *a);
SSL_CTX *q_SSL_CTX_new(const SSL_METHOD *a);
int q_SSL_CTX_set_cipher_list(SSL_CTX *a, const char *b);
int q_SSL_CTX_set_default_verify_paths(SSL_CTX *a);
void q_SSL_CTX_set_verify(SSL_CTX *a, int b, int (*c)(int, X509_STORE_CTX *));
void q_SSL_CTX_set_verify_depth(SSL_CTX *a, int b);
extern "C" {
typedef void (*GenericCallbackType)();
}
long q_SSL_CTX_callback_ctrl(SSL_CTX *, int, GenericCallbackType);
int q_SSL_CTX_use_certificate(SSL_CTX *a, X509 *b);
int q_SSL_CTX_use_certificate_file(SSL_CTX *a, const char *b, int c);
int q_SSL_CTX_use_PrivateKey(SSL_CTX *a, EVP_PKEY *b);
int q_SSL_CTX_use_PrivateKey_file(SSL_CTX *a, const char *b, int c);
X509_STORE *q_SSL_CTX_get_cert_store(const SSL_CTX *a);
SSL_CONF_CTX *q_SSL_CONF_CTX_new();
void q_SSL_CONF_CTX_free(SSL_CONF_CTX *a);
void q_SSL_CONF_CTX_set_ssl_ctx(SSL_CONF_CTX *a, SSL_CTX *b);
unsigned int q_SSL_CONF_CTX_set_flags(SSL_CONF_CTX *a, unsigned int b);
int q_SSL_CONF_CTX_finish(SSL_CONF_CTX *a);
int q_SSL_CONF_cmd(SSL_CONF_CTX *a, const char *b, const char *c);
void q_SSL_free(SSL *a);
STACK_OF(SSL_CIPHER) *q_SSL_get_ciphers(const SSL *a);
const SSL_CIPHER *q_SSL_get_current_cipher(SSL *a);
int q_SSL_version(const SSL *a);
int q_SSL_get_error(SSL *a, int b);
STACK_OF(X509) *q_SSL_get_peer_cert_chain(SSL *a);
long q_SSL_get_verify_result(const SSL *a);
SSL *q_SSL_new(SSL_CTX *a);
SSL_CTX *q_SSL_get_SSL_CTX(SSL *a);
long q_SSL_ctrl(SSL *ssl,int cmd, long larg, void *parg);
int q_SSL_read(SSL *a, void *b, int c);
void q_SSL_set_bio(SSL *a, BIO *b, BIO *c);
void q_SSL_set_accept_state(SSL *a);
void q_SSL_set_connect_state(SSL *a);
int q_SSL_shutdown(SSL *a);
int q_SSL_in_init(const SSL *s);
int q_SSL_get_shutdown(const SSL *ssl);
int q_SSL_set_session(SSL *to, SSL_SESSION *session);
void q_SSL_SESSION_free(SSL_SESSION *ses);
SSL_SESSION *q_SSL_get1_session(SSL *ssl);
SSL_SESSION *q_SSL_get_session(const SSL *ssl);
int q_SSL_set_ex_data(SSL *ssl, int idx, void *arg);
void *q_SSL_get_ex_data(const SSL *ssl, int idx);
#ifndef OPENSSL_NO_PSK
typedef unsigned int (*q_psk_client_callback_t)(SSL *ssl, const char *hint, char *identity, unsigned int max_identity_len, unsigned char *psk, unsigned int max_psk_len);
void q_SSL_set_psk_client_callback(SSL *ssl, q_psk_client_callback_t callback);
typedef unsigned int (*q_psk_server_callback_t)(SSL *ssl, const char *identity, unsigned char *psk, unsigned int max_psk_len);
void q_SSL_set_psk_server_callback(SSL *ssl, q_psk_server_callback_t callback);
int q_SSL_CTX_use_psk_identity_hint(SSL_CTX *ctx, const char *hint);
#endif // !OPENSSL_NO_PSK
int q_SSL_write(SSL *a, const void *b, int c);
int q_X509_cmp(X509 *a, X509 *b);
X509 *q_X509_dup(X509 *a);
void q_X509_print(BIO *a, X509*b);
int q_X509_digest(const X509 *x509, const EVP_MD *type, unsigned char *md, unsigned int *len);
ASN1_OBJECT *q_X509_EXTENSION_get_object(X509_EXTENSION *a);
void q_X509_free(X509 *a);
ASN1_TIME *q_X509_gmtime_adj(ASN1_TIME *s, long adj);
void q_ASN1_TIME_free(ASN1_TIME *t);
X509_EXTENSION *q_X509_get_ext(X509 *a, int b);
int q_X509_get_ext_count(X509 *a);
void *q_X509_get_ext_d2i(X509 *a, int b, int *c, int *d);
const X509V3_EXT_METHOD *q_X509V3_EXT_get(X509_EXTENSION *a);
void *q_X509V3_EXT_d2i(X509_EXTENSION *a);
int q_X509_EXTENSION_get_critical(X509_EXTENSION *a);
ASN1_OCTET_STRING *q_X509_EXTENSION_get_data(X509_EXTENSION *a);
void q_BASIC_CONSTRAINTS_free(BASIC_CONSTRAINTS *a);
void q_AUTHORITY_KEYID_free(AUTHORITY_KEYID *a);
int q_ASN1_STRING_print(BIO *a, const ASN1_STRING *b);
int q_X509_check_issued(X509 *a, X509 *b);
X509_NAME *q_X509_get_issuer_name(X509 *a);
X509_NAME *q_X509_get_subject_name(X509 *a);
ASN1_INTEGER *q_X509_get_serialNumber(X509 *a);
int q_X509_verify_cert(X509_STORE_CTX *ctx);
int q_X509_NAME_entry_count(X509_NAME *a);
X509_NAME_ENTRY *q_X509_NAME_get_entry(X509_NAME *a,int b);
ASN1_STRING *q_X509_NAME_ENTRY_get_data(X509_NAME_ENTRY *a);
ASN1_OBJECT *q_X509_NAME_ENTRY_get_object(X509_NAME_ENTRY *a);
EVP_PKEY *q_X509_PUBKEY_get(X509_PUBKEY *a);
void q_X509_STORE_free(X509_STORE *store);
X509_STORE *q_X509_STORE_new();
int q_X509_STORE_add_cert(X509_STORE *ctx, X509 *x);
void q_X509_STORE_CTX_free(X509_STORE_CTX *storeCtx);
int q_X509_STORE_CTX_init(X509_STORE_CTX *ctx, X509_STORE *store,
                          X509 *x509, STACK_OF(X509) *chain);
X509_STORE_CTX *q_X509_STORE_CTX_new();
int q_X509_STORE_CTX_set_purpose(X509_STORE_CTX *ctx, int purpose);
int q_X509_STORE_CTX_get_error(X509_STORE_CTX *ctx);
int q_X509_STORE_CTX_get_error_depth(X509_STORE_CTX *ctx);
X509 *q_X509_STORE_CTX_get_current_cert(X509_STORE_CTX *ctx);
X509_STORE *q_X509_STORE_CTX_get0_store(X509_STORE_CTX *ctx);

// Diffie-Hellman support
#ifndef OPENSSL_NO_DEPRECATED_3_0
DH *q_DH_new();
void q_DH_free(DH *dh);
int q_DH_check(DH *dh, int *codes);
void q_DH_get0_pqg(const DH *dh, const BIGNUM **p, const BIGNUM **q, const BIGNUM **g);

DH *q_d2i_DHparams(DH **a, const unsigned char **pp, long length);
int q_i2d_DHparams(DH *a, unsigned char **p);

DH *q_PEM_read_bio_DHparams(BIO *a, DH **b, pem_password_cb *c, void *d);
#endif // OPENSSL_NO_DEPRECATED_3_0

BIGNUM *q_BN_bin2bn(const unsigned char *s, int len, BIGNUM *ret);
#define q_SSL_CTX_set_tmp_dh(ctx, dh) q_SSL_CTX_ctrl((ctx), SSL_CTRL_SET_TMP_DH, 0, (char *)dh)
#define q_SSL_CTX_set_dh_auto(ctx, onoff) q_SSL_CTX_ctrl(ctx,SSL_CTRL_SET_DH_AUTO,onoff,NULL)

#ifndef OPENSSL_NO_EC
// EC Diffie-Hellman support
#define q_SSL_CTX_set_tmp_ecdh(ctx, ecdh) q_SSL_CTX_ctrl((ctx), SSL_CTRL_SET_TMP_ECDH, 0, (char *)ecdh)

// EC curves management
size_t q_EC_get_builtin_curves(EC_builtin_curve *r, size_t nitems);
int q_EC_curve_nist2nid(const char *name);
#endif // OPENSSL_NO_EC

#define q_SSL_get_server_tmp_key(ssl, key) q_SSL_ctrl((ssl), SSL_CTRL_GET_SERVER_TMP_KEY, 0, (char *)key)

// PKCS#12 support
int q_PKCS12_parse(PKCS12 *p12, const char *pass, EVP_PKEY **pkey, X509 **cert, STACK_OF(X509) **ca);
PKCS12 *q_d2i_PKCS12_bio(BIO *bio, PKCS12 **pkcs12);
void q_PKCS12_free(PKCS12 *pkcs12);

#define q_BIO_get_mem_data(b, pp) (int)q_BIO_ctrl(b,BIO_CTRL_INFO,0,(char *)pp)
#define q_BIO_pending(b) (int)q_BIO_ctrl(b,BIO_CTRL_PENDING,0,NULL)
#define q_SSL_CTX_set_mode(ctx,op) q_SSL_CTX_ctrl((ctx),SSL_CTRL_MODE,(op),NULL)
#define q_sk_GENERAL_NAME_num(st) q_SKM_sk_num((st))
#define q_sk_GENERAL_NAME_value(st, i) q_SKM_sk_value(GENERAL_NAME, (st), (i))

void q_GENERAL_NAME_free(GENERAL_NAME *a);

#define q_sk_X509_num(st) q_SKM_sk_num((st))
#define q_sk_X509_value(st, i) q_SKM_sk_value(X509, (st), (i))
#define q_sk_SSL_CIPHER_num(st) q_SKM_sk_num((st))
#define q_sk_SSL_CIPHER_value(st, i) q_SKM_sk_value(SSL_CIPHER, (st), (i))
#define q_SSL_CTX_add_extra_chain_cert(ctx,x509) \
        q_SSL_CTX_ctrl(ctx,SSL_CTRL_EXTRA_CHAIN_CERT,0,(char *)x509)
#define q_OpenSSL_add_all_algorithms() q_OPENSSL_add_all_algorithms_conf()

#if OPENSSL_VERSION_MAJOR < 3
int q_SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile, const char *CApath);
#else
int q_SSL_CTX_load_verify_dir(SSL_CTX *ctx, const char *CApath);
#endif // OPENSSL_VERSION_MAJOR

int q_i2d_SSL_SESSION(SSL_SESSION *in, unsigned char **pp);
SSL_SESSION *q_d2i_SSL_SESSION(SSL_SESSION **a, const unsigned char **pp, long length);

#ifndef OPENSSL_NO_NEXTPROTONEG
int q_SSL_select_next_proto(unsigned char **out, unsigned char *outlen,
                            const unsigned char *in, unsigned int inlen,
                            const unsigned char *client, unsigned int client_len);
void q_SSL_CTX_set_next_proto_select_cb(SSL_CTX *s,
                                        int (*cb) (SSL *ssl, unsigned char **out,
                                                   unsigned char *outlen,
                                                   const unsigned char *in,
                                                   unsigned int inlen, void *arg),
                                        void *arg);
void q_SSL_get0_next_proto_negotiated(const SSL *s, const unsigned char **data,
                                      unsigned *len);
int q_SSL_set_alpn_protos(SSL *ssl, const unsigned char *protos,
                          unsigned protos_len);
void q_SSL_CTX_set_alpn_select_cb(SSL_CTX *ctx,
                                  int (*cb) (SSL *ssl,
                                             const unsigned char **out,
                                             unsigned char *outlen,
                                             const unsigned char *in,
                                             unsigned int inlen,
                                             void *arg), void *arg);
void q_SSL_get0_alpn_selected(const SSL *ssl, const unsigned char **data,
                              unsigned *len);
#endif // !OPENSSL_NO_NEXTPROTONEG


#if QT_CONFIG(dtls)

extern "C"
{
typedef int (*CookieGenerateCallback)(SSL *, unsigned char *, unsigned *);
}

void q_SSL_CTX_set_cookie_generate_cb(SSL_CTX *ctx, CookieGenerateCallback cb);
void q_SSL_CTX_set_cookie_verify_cb(SSL_CTX *ctx, CookieVerifyCallback cb);
const SSL_METHOD *q_DTLS_server_method();
const SSL_METHOD *q_DTLS_client_method();

#endif // dtls

void *q_X509_STORE_CTX_get_ex_data(X509_STORE_CTX *ctx, int idx);
int q_SSL_get_ex_data_X509_STORE_CTX_idx();

#if QT_CONFIG(dtls)
#define q_DTLS_set_link_mtu(ssl, mtu) q_SSL_ctrl((ssl), DTLS_CTRL_SET_LINK_MTU, (mtu), nullptr)
#define q_DTLSv1_get_timeout(ssl, arg) q_SSL_ctrl(ssl, DTLS_CTRL_GET_TIMEOUT, 0, arg)
#define q_DTLSv1_handle_timeout(ssl) q_SSL_ctrl(ssl, DTLS_CTRL_HANDLE_TIMEOUT, 0, nullptr)
#endif // dtls

void q_BIO_set_flags(BIO *b, int flags);
void q_BIO_clear_flags(BIO *b, int flags);
void *q_BIO_get_ex_data(BIO *b, int idx);
int q_BIO_set_ex_data(BIO *b, int idx, void *data);

#define q_BIO_set_retry_read(b) q_BIO_set_flags(b, (BIO_FLAGS_READ|BIO_FLAGS_SHOULD_RETRY))
#define q_BIO_set_retry_write(b) q_BIO_set_flags(b, (BIO_FLAGS_WRITE|BIO_FLAGS_SHOULD_RETRY))
#define q_BIO_clear_retry_flags(b) q_BIO_clear_flags(b, (BIO_FLAGS_RWS|BIO_FLAGS_SHOULD_RETRY))
#define q_BIO_set_app_data(s,arg) q_BIO_set_ex_data(s,0,arg)
#define q_BIO_get_app_data(s) q_BIO_get_ex_data(s,0)

#define q_SSL_set_tlsext_status_type(ssl, type) \
    q_SSL_ctrl((ssl), SSL_CTRL_SET_TLSEXT_STATUS_REQ_TYPE, (type), nullptr)

#if QT_CONFIG(ocsp)

OCSP_RESPONSE *q_d2i_OCSP_RESPONSE(OCSP_RESPONSE **a, const unsigned char **in, long len);
int q_i2d_OCSP_RESPONSE(OCSP_RESPONSE *r, unsigned char **ppout);
OCSP_RESPONSE *q_OCSP_response_create(int status, OCSP_BASICRESP *bs);
void q_OCSP_RESPONSE_free(OCSP_RESPONSE *rs);
int q_OCSP_response_status(OCSP_RESPONSE *resp);
OCSP_BASICRESP *q_OCSP_response_get1_basic(OCSP_RESPONSE *resp);
OCSP_SINGLERESP *q_OCSP_basic_add1_status(OCSP_BASICRESP *rsp, OCSP_CERTID *cid,
                                                            int status, int reason, ASN1_TIME *revtime,
                                                            ASN1_TIME *thisupd, ASN1_TIME *nextupd);
int q_OCSP_basic_sign(OCSP_BASICRESP *brsp, X509 *signer, EVP_PKEY *key, const EVP_MD *dgst,
                                        STACK_OF(X509) *certs, unsigned long flags);
OCSP_BASICRESP *q_OCSP_BASICRESP_new();
void q_OCSP_BASICRESP_free(OCSP_BASICRESP *bs);
int q_OCSP_basic_verify(OCSP_BASICRESP *bs, STACK_OF(X509) *certs, X509_STORE *st, unsigned long flags);
int q_OCSP_resp_count(OCSP_BASICRESP *bs);
OCSP_SINGLERESP *q_OCSP_resp_get0(OCSP_BASICRESP *bs, int idx);
int q_OCSP_single_get0_status(OCSP_SINGLERESP *single, int *reason, ASN1_GENERALIZEDTIME **revtime,
                              ASN1_GENERALIZEDTIME **thisupd, ASN1_GENERALIZEDTIME **nextupd);
int q_OCSP_check_validity(ASN1_GENERALIZEDTIME *thisupd, ASN1_GENERALIZEDTIME *nextupd, long nsec, long maxsec);
int q_OCSP_id_get0_info(ASN1_OCTET_STRING **piNameHash, ASN1_OBJECT **pmd, ASN1_OCTET_STRING **pikeyHash,
                        ASN1_INTEGER **pserial, OCSP_CERTID *cid);

const STACK_OF(X509) *q_OCSP_resp_get0_certs(const OCSP_BASICRESP *bs);
OCSP_CERTID *q_OCSP_cert_to_id(const EVP_MD *dgst, X509 *subject, X509 *issuer);
void q_OCSP_CERTID_free(OCSP_CERTID *cid);
int q_OCSP_id_cmp(OCSP_CERTID *a, OCSP_CERTID *b);

#define q_SSL_get_tlsext_status_ocsp_resp(ssl, arg) \
    q_SSL_ctrl(ssl, SSL_CTRL_GET_TLSEXT_STATUS_REQ_OCSP_RESP, 0, arg)

#define q_SSL_CTX_set_tlsext_status_cb(ssl, cb) \
    q_SSL_CTX_callback_ctrl(ssl, SSL_CTRL_SET_TLSEXT_STATUS_REQ_CB, GenericCallbackType(cb))

# define q_SSL_set_tlsext_status_ocsp_resp(ssl, arg, arglen) \
    q_SSL_ctrl(ssl, SSL_CTRL_SET_TLSEXT_STATUS_REQ_OCSP_RESP, arglen, arg)

#endif // ocsp


void *q_CRYPTO_malloc(size_t num, const char *file, int line);
#define q_OPENSSL_malloc(num) q_CRYPTO_malloc(num, "", 0)
void q_CRYPTO_free(void *str, const char *file, int line);
# define q_OPENSSL_free(addr) q_CRYPTO_free(addr, "", 0)
int q_CRYPTO_memcmp(const void * in_a, const void * in_b, size_t len);

void q_SSL_set_info_callback(SSL *ssl, void (*cb) (const SSL *ssl, int type, int val));
const char *q_SSL_alert_type_string(int value);
const char *q_SSL_alert_desc_string_long(int value);

int q_SSL_CTX_get_security_level(const SSL_CTX *ctx);
void q_SSL_CTX_set_security_level(SSL_CTX *ctx, int level);

// Here we have the ones that make difference between OpenSSL pre/post v3:
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 3
X509 *q_SSL_get1_peer_certificate(SSL *a);
#define q_SSL_get_peer_certificate q_SSL_get1_peer_certificate
int q_EVP_PKEY_get_bits(const EVP_PKEY *pkey);
int q_EVP_PKEY_get_base_id(const EVP_PKEY *pkey);
#define q_EVP_PKEY_base_id q_EVP_PKEY_get_base_id
#else
X509 *q_SSL_get_peer_certificate(SSL *a);
int q_EVP_PKEY_base_id(EVP_PKEY *a);
#endif // OPENSSL_VERSION_MAJOR >= 3

#ifndef OPENSSL_NO_DEPRECATED_3_0

DSA *q_DSA_new();
void q_DSA_free(DSA *a);

RSA *q_RSA_new();
void q_RSA_free(RSA *a);

#ifndef OPENSSL_NO_EC

EC_KEY *q_EC_KEY_dup(const EC_KEY *src);
EC_KEY *q_EC_KEY_new_by_curve_name(int nid);
void q_EC_KEY_free(EC_KEY *ecdh);

#endif // OPENSSL_NO_EC

int q_SSL_CTX_use_RSAPrivateKey(SSL_CTX *a, RSA *b);

DSA *q_PEM_read_bio_DSA_PUBKEY(BIO *a, DSA **b, pem_password_cb *c, void *d);
RSA *q_PEM_read_bio_RSA_PUBKEY(BIO *a, RSA **b, pem_password_cb *c, void *d);

DSA *q_PEM_read_bio_DSAPrivateKey(BIO *a, DSA **b, pem_password_cb *c, void *d);
RSA *q_PEM_read_bio_RSAPrivateKey(BIO *a, RSA **b, pem_password_cb *c, void *d);

int q_PEM_write_bio_DSA_PUBKEY(BIO *a, DSA *b);
int q_PEM_write_bio_RSA_PUBKEY(BIO *a, RSA *b);

int q_PEM_write_bio_DSAPrivateKey(BIO *a, DSA *b, const EVP_CIPHER *c, unsigned char *d,
                                  int e, pem_password_cb *f, void *g);
int q_PEM_write_bio_RSAPrivateKey(BIO *a, RSA *b, const EVP_CIPHER *c, unsigned char *d,
                                  int e, pem_password_cb *f, void *g);

RSA *q_EVP_PKEY_get1_RSA(EVP_PKEY *a);
DSA *q_EVP_PKEY_get1_DSA(EVP_PKEY *a);
DH *q_EVP_PKEY_get1_DH(EVP_PKEY *a);

int q_EVP_PKEY_set1_RSA(EVP_PKEY *a, RSA *b);
int q_EVP_PKEY_set1_DSA(EVP_PKEY *a, DSA *b);
int q_EVP_PKEY_set1_DH(EVP_PKEY *a, DH *b);

int q_DH_bits(DH *dh);
int q_RSA_bits(RSA *a);
int q_DSA_bits(DSA *a);

int q_EVP_PKEY_assign(EVP_PKEY *a, int b, void *r);
int q_EVP_PKEY_cmp(const EVP_PKEY *a, const EVP_PKEY *b);

#ifndef OPENSSL_NO_EC

EC_KEY *q_PEM_read_bio_EC_PUBKEY(BIO *a, EC_KEY **b, pem_password_cb *c, void *d);
EC_KEY *q_PEM_read_bio_ECPrivateKey(BIO *a, EC_KEY **b, pem_password_cb *c, void *d);

int q_PEM_write_bio_ECPrivateKey(BIO *a, EC_KEY *b, const EVP_CIPHER *c, unsigned char *d,
                                  int e, pem_password_cb *f, void *g);
int q_PEM_write_bio_EC_PUBKEY(BIO *a, EC_KEY *b);

EC_KEY *q_EVP_PKEY_get1_EC_KEY(EVP_PKEY *a);
int q_EVP_PKEY_set1_EC_KEY(EVP_PKEY *a, EC_KEY *b);

const EC_GROUP* q_EC_KEY_get0_group(const EC_KEY* k);
int q_EC_GROUP_get_degree(const EC_GROUP* g);

#define q_EVP_PKEY_assign_RSA(pkey,rsa) q_EVP_PKEY_assign((pkey),EVP_PKEY_RSA,\
                                        (char *)(rsa))
#define q_EVP_PKEY_assign_DSA(pkey,dsa) q_EVP_PKEY_assign((pkey),EVP_PKEY_DSA,\
                                        (char *)(dsa))


#endif // OPENSSL_NO_EC

#endif // OPENSSL_NO_DEPRECATED_3_0

QT_END_NAMESPACE

#endif
