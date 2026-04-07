#include "bochs/bochs.h"
#include "bochs/cpu/decoder/instr.h"
#include "bochs/cpu/decoder/decoder.h"
#include "bochs/cpu/decoder/fetchdecode.h"
#include <iostream>

extern int fetchDecode32(const Bit8u *fetchPtr, bool is_32, bxInstruction_c *i, unsigned remainingInPage);
#if BX_SUPPORT_X86_64
extern int fetchDecode64(const Bit8u *fetchPtr, bxInstruction_c *i, unsigned remainingInPage);
#endif

int main()
{
    char disbuf[100] = {0};
    Bit8u instr[] = {0x67,0x48,0x8d, 0x00};
    bxInstruction_c i = {0};
    bx_address cs_base = 0;
    bx_address ip = 0;
    if (disbuf == disasm(instr, 0, 1, disbuf, &i, cs_base, ip, BX_DISASM_INTEL))
    {
        i.set_opcode_bytes(instr);
        std::cout << i.ilen() << std::endl;
        std::cout << disbuf << std::endl;
    }
    //    extern bxIAOpcodeTable BxOpcodesTable[];
    //    Bit16u ia_opcode = i.getIaOpcode();
    //    int lenImm = 0;
    // 			for (unsigned n = 0; n <= 3; n++) {
    //     			unsigned type_src = (unsigned)BxOpcodesTable[ia_opcode].src[n];
    // 				unsigned type = BX_DISASM_SRC_TYPE(type_src);
    // 				unsigned src = BX_DISASM_SRC_ORIGIN(type_src);
    // 				if (src == BX_SRC_IMM)
    // 				{
    // 					switch(type) {
    // 							case BX_IMM1:
    // 							case BX_IMMB:
    // 							case BX_IMMBW_SE:
    // 							case BX_IMMBD_SE:
    // 							case BX_IMMB2:
    // 								lenImm++;
    // 								break;
    // 							case BX_IMMW:
    // 								lenImm += 2;
    // 								break;
    // 							case BX_IMMD:
    // 								lenImm += 4;
    // 					}
    // 				}
    // 			}
    //             std::cout << lenImm << std::endl;
    return 0;
}