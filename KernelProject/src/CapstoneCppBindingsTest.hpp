#pragma once

#include <cccapstone/cppbindings/X86Disasm.h>

namespace CapstoneBindingsTest
{
#define RANDOM_CODE "\xed\x00\x00\x00\x00\x1a\x5a\x0f\x1f\xff\xc2\x09\x80\x00\x00\x00\x07\xf7\xeb\x2a\xff\xff\x7f\x57\xe3\x01\xff\xff\x7f\x57\xeb\x00\xf0\x00\x00\x24\xb2\x4f\x00\x78"

	static 
	size_t 
	SkipDataCallback(
		__in const uint8_t *buffer, 
		__in uint64_t offset, 
		__in void *p
		)
	{
		printf("\nskip data callback ! : %x %p !", offset, buffer);
		return 1;//just for test, skip 1instr *data*
	}

	static
	void 
	DisasmData(
		__in CX86Arch& dis,
		__in const void* code,
		__in size_t size
		)
	{
		auto insn = dis.Disasm(code, size);
		if (!insn.get())
			return;

		printf("\n\nDISASM :\n\n");
		for (size_t i = 0; i < insn->Count; i++)
		{
			printf("-> 0x%p:\t%s\t%s\n", insn->Instructions[i].address, insn->Instructions[i].mnemonic, insn->Instructions[i].op_str);
			dis.PrintInstDetail(insn->Instructions[i]);

			//TODO
	#if 0
			if (!dis.IsInInsGroup(insn->Instructions[i], x86_insn_group::X86_GRP_JUMP))
				continue;

			printf("\nCONTROL FLOW CHANGE instruction detected!\n");
			printf("-> 0x%p:\t%s\t%s\n", insn->Instructions[i].address, insn->Instructions[i].mnemonic, insn->Instructions[i].op_str);
	#endif
		}
	}

	static
	void
	X64Disasm(
		__in const void* code,
		__in size_t size,
		__in bool allInfo = false
		)
	{
		CX86Disasm64 dis;
		if (dis.GetError())
			return;

		DisasmData(dis, code, size);
	}

	static
	void 
	X64DisasmCallback(
		__in const void* code,
		__in size_t size,
		__in bool allInfo = false
		)
	{
		CX86Disasm64 dis;
		if (dis.GetError())
			return;

		if (allInfo)
			dis.SetDetail(cs_opt_value::CS_OPT_ON);

		dis.SetSkipDataCallback(cs_opt_skipdata{ ".UNKOWNBYTES : ", SkipDataCallback, nullptr });
		DisasmData(dis, code, size);
	}
};
