from pwn import *
import gen

sh = process('test/test')

gdb.attach(sh)

sh.send(gen.my_asm('./source.c', opt=True))

sh.interactive()

