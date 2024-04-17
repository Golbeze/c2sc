#!/usr/bin/env python3
from pwn import *
import os
import re
import tempfile
import subprocess
import pathlib

def run_cmd_with_check(cmd):
    try:
        subprocess.check_output(cmd, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        print("Command failed. Error message:")
        print(e.output.decode())
        raise

def run_cmds(cmds):
    for cmd in cmds:
        run_cmd_with_check(cmd)

def get_includes(file):
    fd = open(file, 'r')
    ctt = re.findall(r"#include.*", fd.read())
    ctt = '\n'.join(ctt)
    fd.close()
    return ctt

def gen_defs(file : str = "./source.c", target_path = './defs.h'):
    pathlib.Path(target_path).unlink(missing_ok=True)
    ctt = get_includes(file).encode()
    with tempfile.NamedTemporaryFile() as fp:
        fp.write(ctt)
        fp.flush()
        cmds = [
            ['cpp', '-E', '-dD', fp.name, '-o', target_path]
            # ['gcc', file, '-o', fp.name, '-g'],
        ]
        run_cmds(cmds)
        # cmd = ['pahole', '--compile', fp.name]   # 用pahole提取elf调试信息中的类型信息导出成头文件
        # run_cmd_append_file(cmd, def_file)
    fd = open(target_path, 'r')
    ctt = fd.read()
    ctt = re.sub(r"(__extension__)?\s*extern[^;{]+;",'',ctt)        # strip extern function
    ctt = re.sub('\n{4,}','\n',ctt)                                  # trim lines
    fd.close()

    fd = open(target_path, 'w')
    fd.write(ctt)
    fd.close()

def strip_include(file : str = './source.c'):
    ctt = open(file, 'r').read()
    ctt = re.sub('#include.*\n','',ctt)
    fp = open('./shellcode.c', 'w')
    fp.write('''
#include "mysyscall.h"
''')
    fp.write(ctt)
    name = fp.name
    fp.close()
    return name


def my_asm(file : str = "./source.c", opt=False, strip_tailing_zeros=True):
    gen_defs(file)
    file = strip_include(file)

    cmd = [
        'gcc',
        '-S',
        '-w',
        '-nostdlib',
        '-fno-asynchronous-unwind-tables',
        '-fdata-sections',
        '-fomit-frame-pointer',
        '-ffunction-sections',
        '-fPIE',
        '-fcf-protection=none'
    ]

    if opt:
        cmd.append('-Os')

    cmd.extend([
        '-o', '/tmp/output.s',
        file
    ])
    run_cmd_with_check(cmd)

    cmds = [
        [
            'as',
            '-64',
            '-o', '/tmp/output.o',
            '/tmp/output.s'
        ],
        [
            'gcc', 
            '/tmp/output.o', 
            '-Wl,--gc-sections', 
            '-Wl,--no-dynamic-linker', 
            '-T', './script.ld', 
            '-o', '/tmp/output.elf'
        ],
        [
            'objcopy',
            '-j', '.shellcode',
            '-Obinary',
            '/tmp/output.elf',
            '/tmp/output.elf.bytes'
        ]
    ]
    run_cmds(cmds)

    code = open('/tmp/output.elf.bytes', 'rb').read()
    if strip_tailing_zeros:
        code = code.rstrip(b'\x00')
    return code

shellcode = my_asm(opt=True)


# success("shellcode len : "+hex(len(asm(shellcraft.mmap(0, 0x1000, 3, 0x22, 0xffffffff, 0) + shellcraft.read(0,'rax', 0x30)))))
# sh = process('./test')

# gdb.attach(sh,'brva 0x11eb\nc\n')
# sh.send(shellcode)

# sh.interactive()

