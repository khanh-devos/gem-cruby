#include <khanh.h>
#include <sys/sysinfo.h>

struct sysinfo buf;

VALUE check_loadavg(VALUE self) {
  char status = sysinfo(&buf);
  if (status == -1) return Qnil;

  // check ram
  unsigned long long oneG = pow(1024, 3);
//   printf("total Ram %d GiB \n", (unsigned long long)buf.totalram / oneG);  
//   printf("free Ram %d GiB \n", (unsigned long long)buf.freeram / oneG);  
//   printf("shared Ram %d B \n", (unsigned long long)buf.sharedram);  
//   printf("buffer Ram %d B \n", (unsigned long long)buf.bufferram);  
//   printf("total swap %d B \n", (unsigned long long)buf.totalswap);  

  // Others
  long double load = 1.0 / (1 << SI_LOAD_SHIFT);
  long double load1 = buf.loads[0] * load;  
  long double load2 = buf.loads[1] * load;
  long double load3 = buf.loads[2] * load;
  // printf: %d int, %f float, %lf double, %Lf long double || %c char, %s string

  // Ter: gcc sysinfo.c && ./a.out
  // MOTE EXACTLY, Ter: ./a.out && cat /proc/loadavg
  return rb_ary_new_from_args(3, 
    DBL2NUM(load1), 
    DBL2NUM(load2), 
    DBL2NUM(load3)
  );
}

VALUE check_totalram(VALUE self) {
  char status = sysinfo(&buf);
  if (status == -1) return Qnil;

  double long mem_unit = buf.mem_unit;
  double long oneGB = pow(1024, 3);
  double long total_ram = buf.totalram * mem_unit / oneGB;
  
  char str[100];
  sprintf(str, "%Lf GiB", total_ram);
  
  return rb_str_new_cstr(str);

}


// how long is it since the boot time?
VALUE check_uptime(VALUE self) {
    char status = sysinfo(&buf);
    if (status == -1) return Qnil;
    char str[100];
    sprintf(str, "%ld mins", buf.uptime/60);

    // %d--> for int
    // %u--> for unsigned int
    // %ld--> for long int or long
    // %lu--> for unsigned long int or long unsigned int or unsigned long
    // %lld--> for long long int or long long
    // %llu--> for unsigned long long int or unsigned long long

    return rb_str_new_cstr(str);

}

void Init_sysinfo(VALUE self) {
  rb_define_singleton_method(mKhanh, "loadavg", check_loadavg, 0);
  rb_define_singleton_method(mKhanh, "uptime", check_uptime, 0);
  rb_define_singleton_method(mKhanh, "totalram", check_totalram, 0);
  
  // Set global
  rb_define_global_function("loadavg", check_loadavg, 0);
  rb_define_global_function("uptime", check_uptime, 0);
  rb_define_global_function("totalram", check_totalram, 0);
}