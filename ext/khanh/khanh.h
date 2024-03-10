
#include <ruby.h>
#include <string.h>
#include <ctype.h> 
#include <regex.h>

#if 0
  mKhanh = rb_define_module("Khanh");
  cCRuby = cCRuby = rb_define_class_under(mKhanh, "CRuby", rb_cObject);
#endif

extern VALUE mKhanh;
extern VALUE cCRuby;