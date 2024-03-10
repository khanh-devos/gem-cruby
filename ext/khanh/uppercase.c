#include <khanh.h>

VALUE string_upper(VALUE self) {
  char* cStr = StringValuePtr(self); //convert a C string from a ruby string
  int i = 0; 
  int j = strlen(cStr);
  char n[j], left;

  while (left = cStr[i]) {
    n[i] = toupper(left);
    ++i;
  }

  n[j] = '\0';
  return rb_str_new_cstr(n);
}

void Init_uppercase(void) {
  VALUE rb_string = rb_define_class("String", rb_cObject); ;
  rb_define_method(rb_string, "cUpcase", string_upper, 0);
  // Now we can call "abc".cUpcase => "ABC". 
  // Same built-in method: "abc".upcase()
}