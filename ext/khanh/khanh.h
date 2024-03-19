
#include <ruby.h>
#include <string.h>
#include <ctype.h> 
#include <regex.h>
#include <math.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/opensslv.h>

#include <openssl/err.h>
#include <openssl/asn1.h>
#include <openssl/x509v3.h>
#include <openssl/ssl.h>
#include <openssl/pkcs12.h>
#include <openssl/pkcs7.h>
#include <openssl/rand.h>
#include <openssl/conf.h>

#ifndef OPENSSL_NO_TS
  #include <openssl/ts.h>
#endif
#include <openssl/crypto.h>
#if !defined(OPENSSL_NO_OCSP)
#  include <openssl/ocsp.h>
#endif
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/dsa.h>
#include <openssl/dh.h>


#if 0
  mKhanh = rb_define_module("Khanh");
  cCRuby = cCRuby = rb_define_class_under(mKhanh, "CRuby", rb_cObject);
#endif

extern VALUE mKhanh;
extern VALUE cCRuby;
extern VALUE cDigest;