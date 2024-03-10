#include <khanh.h>

// declase a new structure(new type) "my_malloc"
struct my_malloc {
  size_t size;      // size_t garantees not negative.
  void *ptr;        // refer to the data 
};

static void
my_malloc_free(void *p) {
  // create an object "ptr" of struct type "my_malloc"
  struct my_malloc *ptr = p;    

  if (ptr->size > 0)
    free(ptr->ptr);     // clear out the memory of object "ptr"
}

static VALUE
my_malloc_alloc(VALUE klass) {
  VALUE obj;
  struct my_malloc *ptr;

  obj = Data_Make_Struct(klass, struct my_malloc, NULL, my_malloc_free, ptr);

  ptr->size = 0;
  ptr->ptr  = NULL;

  return obj;
}

static VALUE
my_malloc_init(VALUE self, VALUE size) {
  struct my_malloc *ptr;
  size_t requested = NUM2SIZET(size);

  if (0 == requested)
    rb_raise(rb_eArgError, "unable to allocate 0 bytes");

  Data_Get_Struct(self, struct my_malloc, ptr);

  ptr->ptr = malloc(requested);

  if (NULL == ptr->ptr)
    rb_raise(rb_eNoMemError, "unable to allocate %ld bytes", requested);

  ptr->size = requested;
//   rb_gv_set("$a", requested);

  return self;
}

static VALUE
my_malloc_release(VALUE self) {
  struct my_malloc *ptr;

  Data_Get_Struct(self, struct my_malloc, ptr);

  if (0 == ptr->size)
    return self;

  ptr->size = 0;
  free(ptr->ptr);

  return self;
}

VALUE 
check(VALUE self) {
  struct my_malloc *ptr;

  Data_Get_Struct(self, struct my_malloc, ptr);
  ptr->size = 0;
  free(ptr->ptr);

  return INT2FIX(ptr->size);
}

// globalize these variables
VALUE mKhanh;
VALUE cCRuby;

void
Init_khanh(void) {
  
  /*
  * Init main module
  */
  mKhanh = rb_define_module("Khanh");
  cCRuby = rb_define_class_under(mKhanh, "CRuby", rb_cObject);


  rb_define_alloc_func(cCRuby, my_malloc_alloc);
  rb_define_method(cCRuby, "initialize", my_malloc_init, 1);
  rb_define_method(cCRuby, "free", my_malloc_release, 0);
  rb_define_method(cCRuby, "check", check, 0);

  // run other C modules
  Init_fibonacy();
  Init_uppercase();
  Init_sysinfo();
}