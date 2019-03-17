//@ Including Header
\#include <csl_std.h>

/**
 *  Name : ${FILE_NAME}
 *  Date : ${DATE} ${TIME}
 *  Copyright : chouun.com
 *  Anti-Mage : The magic ends here.
 */
 
//@ Main Function
int Main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int _, __ = 1;
  for(std::cin >> _; _; --_, ++__) {
    //std::cout << "Case #" << __ << ": ";

  }
  return 0;
}

//@ Anti Stack Overflow
// \#define ANTI_STACK_OVERFLOW
int main() {
#ifdef ANTI_STACK_OVERFLOW
  std::size_t size = 16 << 20; // KB(<<10), MB(<<20).
  char* data = (char*)malloc(size) + size;
\#if __x86_64__ || __ppc64__ || _WIN64
  __asm__ __volatile__("movq %0, %%rsp \n pushq \$_exit \n" ::"r"(data));
\#else
  __asm__ __volatile__("movl %0, %%esp \n pushl \$_exit \n" ::"r"(data));
#endif
#endif
  exit(Main());
}
