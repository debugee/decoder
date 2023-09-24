#include "bochs.h"
#include "instr.h"

extern int fetchDecode32(const Bit8u *fetchPtr, bool is_32, bxInstruction_c *i, unsigned remainingInPage);
#if BX_SUPPORT_X86_64
extern int fetchDecode64(const Bit8u *fetchPtr, bxInstruction_c *i, unsigned remainingInPage);
#endif

int main()
{
    char disbuf[100] = {0};
    Bit8u instr[] = {0x29,0xc0};
    bxInstruction_c i = {0};
    bx_address cs_base = 0;
    bx_address ip = 0;
    //int ret = fetchDecode64(instr, &i, 3);

    if (disbuf == disasm(instr, 0, 1, disbuf, &i, cs_base, ip, BX_DISASM_INTEL))
    {
        i.set_opcode_bytes(instr);
    }

    return 0;
}