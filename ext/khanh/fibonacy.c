#include <khanh.h>


VALUE fib(VALUE obj) {
  unsigned long long a=0, b=1, i=0, range=NUM2ULL(obj), temp;
  VALUE cArr = rb_ary_new_from_args(1, INT2FIX(a));


  while(i++ < range) {
    temp = b;
    b = a + b;
    a = temp; 

    rb_ary_push(cArr, INT2FIX(a));

  }

  return cArr;

}

#define PLUS rb_intern("+")

VALUE bigFib(VALUE obj, VALUE n) {
  unsigned long long i=0, range=NUM2ULL(n);
  VALUE a = INT2FIX(0), b = INT2FIX(1), temp;

  VALUE cArr = rb_ary_new_from_args(1, a);
  VALUE plus = rb_intern("+");

  while(i++ < range) {
    temp = b;
    b = rb_funcall(a, plus, 1, b);
    a = temp;

    rb_ary_push(cArr, a);

  }

  return cArr;

}

void Init_fibonacy(void) {
  // Add a new method to class Khanh
  rb_define_singleton_method(cCRuby, "bigFib", bigFib, 1);
  
  
  // Add a new method into default class Integer:
  // rb_cNumeric : 'c' is a class and 'm' is a module mNumeric
  // check String.ancestors and Integer.ancestors.
  VALUE _integer = rb_define_class("Integer", rb_cNumeric); 
  rb_define_method(_integer, "fib", fib, 0);
  
}