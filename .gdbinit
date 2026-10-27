#use for 386 and 8086
# 1. 设置反汇编语法为 Intel 风格
set disassembly-flavor intel

# 2. 关闭gdb自动disasm
set print frame-arguments none

file /Users/admin/Desktop/decoder/install/boot.elf

# 3. 自动化智能寻址与反汇编宏
define auto_disasm
    # 通过强制类型转换为全局指针，提取出 CS 的纯数值，防止 GDB 报错
    set $raw_cs = (unsigned int)$cs
    set $raw_eip = (unsigned int)$eip

    # 判断模式：如果 CS 的值是现代保护模式常用的段选择子（如 0x08），则判定为保护模式
    if $raw_cs == 0x08
        # ----------------- 保护模式 -----------------
        set architecture i386
        echo [Protected Mode] Linear Address: \n
        x/3i $raw_eip
    else
        # ----------------- 实模式 -----------------
        set architecture i8086
        # 自动且实时地根据当前数字计算物理地址：(CS << 4) + IP
        set $phys_pc = (($raw_cs & 0xFFFF) << 4) + ($raw_eip & 0xFFFF)
        printf "[Real Mode] CS:IP = 0x%04X:0x%04X  =>  Physical PC = 0x%05X\n", $raw_cs, $raw_eip, $phys_pc
        x/3i $phys_pc
    end
end

# 4. 挂载钩子，让每次停下只执行我们正确的反汇编
define hook-stop
    auto_disasm
end

target remote localhost:1234