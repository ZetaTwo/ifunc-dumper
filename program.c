#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_NUM_IMPL 256

//From "include/ifunc-impl-list.h"
struct libc_ifunc_impl
{
  /* The name of function to be tested.  */
  const char *name;
  /* The address of function to be tested.  */
  void (*fn) (void);
  /* True if this implementation is usable on this machine.  */
  bool usable;
};

extern size_t __libc_ifunc_impl_list (const char *name, struct libc_ifunc_impl *array, size_t max);
extern const char* function_names[];

uintptr_t find_libc_base() {
    uintptr_t libc_pointer;
    for(libc_pointer = (uintptr_t)printf & (~0xFFF); *(uint32_t*)libc_pointer != 0x464c457f; libc_pointer-=0x1000);
    return libc_pointer;
}

int main() {
    struct libc_ifunc_impl entries[MAX_NUM_IMPL];
    uintptr_t libc_base = find_libc_base();

    for(const char** function_name = function_names; *function_name; function_name++) {
        size_t num_entries = __libc_ifunc_impl_list(*function_name, entries, MAX_NUM_IMPL);
        for(size_t i = 0; i < num_entries; i++) {
            printf("%p %s\n", (void*)((uintptr_t)entries[i].fn - (uintptr_t)libc_base), entries[i].name);
        }
    }

    return 0;
}
