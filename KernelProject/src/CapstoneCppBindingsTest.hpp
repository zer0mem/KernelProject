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
		__in size_t size
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
		__in size_t size
		)
	{
		CX86Disasm64 dis(
			cs_mode::CS_MODE_64 + cs_mode::CS_MODE_LITTLE_ENDIAN,
			cs_opt_type::CS_OPT_DETAIL,
			cs_opt_value::CS_OPT_ON,
			"skip callbacks setup for intel x64",
			cs_opt_type::CS_OPT_SKIPDATA_SETUP,
			cs_opt_skipdata { ".db", SkipDataCallback, CCppDriver::GetInstance().DriverObject() });

		if (dis.GetError())
			return;
		DisasmData(dis, code, size);
	}
};
