/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL licenses, (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * https://www.openssl.org/source/license.html
 * or in the file LICENSE in the source distribution.
 */


#include "dh_locl.h"
#include <string.h>

DH_METHOD *DH_meth_new(const char *name, int flags)
{
    DH_METHOD *dhm = OPENSSL_zalloc(sizeof(DH_METHOD));

    if (dhm != NULL) {
        dhm->name = OPENSSL_strdup(name);
        dhm->flags = flags;
    }

    return dhm;
}

void DH_meth_free(DH_METHOD *dhm)
{
    if (dhm != NULL) {
        if (dhm->name != NULL)
            OPENSSL_free(dhm->name);
        OPENSSL_free(dhm);
    }
}

DH_METHOD *DH_meth_dup(const DH_METHOD *dhm)
{
    DH_METHOD *ret;

    ret = OPENSSL_malloc(sizeof(DH_METHOD));

    if (ret != NULL) {
        memcpy(ret, dhm, sizeof(*dhm));
        ret->name = OPENSSL_strdup(dhm->name);
    }

    return ret;
}

const char *DH_meth_get0_name(const DH_METHOD *dhm)
{
    return dhm->name;
}

int DH_meth_set1_name(DH_METHOD *dhm, const char *name)
{
    OPENSSL_free(dhm->name);
    dhm->name = OPENSSL_strdup(name);

    return dhm->name != NULL;
}

int DH_meth_get_flags(DH_METHOD *dhm)
{
    return dhm->flags;
}

int DH_meth_set_flags(DH_METHOD *dhm, int flags)
{
    dhm->flags = flags;
    return 1;
}

void *DH_meth_get0_app_data(const DH_METHOD *dhm)
{
    return dhm->app_data;
}

int DH_meth_set0_app_data(DH_METHOD *dhm, void *app_data)
{
    dhm->app_data = app_data;
    return 1;
}

int (*DH_meth_get_generate_key(const DH_METHOD *dhm)) (DH *)
{
    return dhm->generate_key;
}

int DH_meth_set_generate_key(DH_METHOD *dhm, int (*generate_key) (DH *))
{
    dhm->generate_key = generate_key;
    return 1;
}

int (*DH_meth_get_compute_key(const DH_METHOD *dhm))
        (unsigned char *key, const BIGNUM *pub_key, DH *dh)
{
    return dhm->compute_key;
}

int DH_meth_set_compute_key(DH_METHOD *dhm,
        int (*compute_key) (unsigned char *key, const BIGNUM *pub_key, DH *dh))
{
    dhm->compute_key = compute_key;
    return 1;
}


int (*DH_meth_get_bn_mod_exp(const DH_METHOD *dhm))
    (const DH *, BIGNUM *, const BIGNUM *, const BIGNUM *, const BIGNUM *,
     BN_CTX *, BN_MONT_CTX *)
{
    return dhm->bn_mod_exp;
}

int DH_meth_set_bn_mod_exp(DH_METHOD *dhm,
    int (*bn_mod_exp) (const DH *, BIGNUM *, const BIGNUM *, const BIGNUM *,
                       const BIGNUM *, BN_CTX *, BN_MONT_CTX *))
{
    dhm->bn_mod_exp = bn_mod_exp;
    return 1;
}

int (*DH_meth_get_init(const DH_METHOD *dhm))(DH *)
{
    return dhm->init;
}

int DH_meth_set_init(DH_METHOD *dhm, int (*init)(DH *))
{
    dhm->init = init;
    return 1;
}

int (*DH_meth_get_finish(const DH_METHOD *dhm)) (DH *)
{
    return dhm->finish;
}

int DH_meth_set_finish(DH_METHOD *dhm, int (*finish) (DH *))
{
    dhm->finish = finish;
    return 1;
}

int (*DH_meth_get_generate_params(const DH_METHOD *dhm))
        (DH *, int, int, BN_GENCB *)
{
    return dhm->generate_params;
}

int DH_meth_set_generate_params(DH_METHOD *dhm,
        int (*generate_params) (DH *, int, int, BN_GENCB *))
{
    dhm->generate_params = generate_params;
    return 1;
}
