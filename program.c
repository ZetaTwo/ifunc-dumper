#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

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

const char* function_names[] = {
    "__memcpy_chk",
    "__memmove_chk",
    "__mempcpy_chk",
    "__memset_chk",
    "__wmemset_chk",
    "memchr",
    "memcmp",
    "memcpy",
    "memmove",
    "mempcpy",
    "memrchr",
    "memset",
    "rawmemchr",
    "stpcpy",
    "stpncpy",
    "strcasecmp",
    "strcasecmp_l",
    "strcat",
    "strchr",
    "strchrnul",
    "strcmp",
    "strcpy",
    "strcspn",
    "strlen",
    "strncasecmp",
    "strncasecmp_l",
    "strncat",
    "strncmp",
    "strncpy",
    "strnlen",
    "strpbrk",
    "strrchr",
    "strspn",
    "strstr",
    "wcschr",
    "wcscmp",
    "wcscpy",
    "wcslen",
    "wcsncmp",
    "wcsnlen",
    "wcsrchr",
    "wmemchr",
    "wmemcmp",
    "wmemset", 
    NULL
};

uintptr_t find_libc_base() {
    uintptr_t libc_pointer;
    for(libc_pointer = (uintptr_t)printf & (~0xFFF); *(uint32_t*)libc_pointer != 0x464c457f; libc_pointer-=0x1000);
    return libc_pointer;
}

int main() {
    struct libc_ifunc_impl entries[128];
    uintptr_t libc_base = find_libc_base();

    for(const char** function_name = function_names; *function_name; function_name++) {
        size_t num_entries = __libc_ifunc_impl_list(*function_name, entries, 128);
        for(size_t i = 0; i < num_entries; i++) {
            printf("%p %s\n", (void*)(entries[i].fn - libc_base), entries[i].name);
        }
    }

    return 0;
}
