# GNU IFUNC offset dumper

The GNU indirect function support (IFUNC) is a feature of the GNU toolchain that allows a developer to create multiple implementations of a given function and to select amongst them at runtime using a resolver function which is also written by the developer. More info: https://sourceware.org/glibc/wiki/GNU_IFUNC

These various implementations are not exposed in the symbols table or any other static resource. It is therefore difficult to get the offsets of these functions which are sometimes useful in some program analysis scenarios such as exploit development.

This tool loads the list of IFUNC functions in libc and prints out the function names and their offsets. This can then be used in further work.

```
> make
> ./ifunc-resolver 
0x18d360 __memcpy_chk_avx512_no_vzeroupper
0x18dd50 __memcpy_chk_avx512_unaligned
0x18ddc0 __memcpy_chk_avx512_unaligned_erms
0x189010 __memcpy_chk_avx_unaligned
0x189070 __memcpy_chk_avx_unaligned_erms
0x168e20 __memcpy_chk_ssse3_back
0x1638b0 __memcpy_chk_ssse3
...
```

If you want to use this on a different libc version, you can load that with LD_PRELOAD.

```
> make
> LD_PRELOAD=$(pwd)/libc-2.13.37.so ./ifunc-resolver 
0x18d360 __memcpy_chk_avx512_no_vzeroupper
0x18dd50 __memcpy_chk_avx512_unaligned
...
```
