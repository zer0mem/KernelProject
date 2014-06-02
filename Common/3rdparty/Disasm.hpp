#pragma once

#include "drv_common.h"

#include <capstone.h>
#include <memory>

#include "InsInfo.hpp"

struct CS_PLATFORM
{
	cs_arch Arch;
	cs_mode Mode;
	const char* Comment;
	cs_opt_type OptType;
	cs_opt_value OptValue;
};

struct CS_HANDLE :
	protected std::unique_ptr<csh, decltype(&cs_close)>
{
	csh Handle;
	CS_HANDLE() :
		std::unique_ptr<csh, decltype(&cs_close)>(&Handle, cs_close)
	{
	}
};

struct CS_INSN_HOLDER
{
	size_t Size;
	const void* Address;

	size_t Count;
	cs_insn* Instructions;

	CS_INSN_HOLDER(
		__in const void* address,
		__in size_t size
		) : Address(address), 
			Size(size)
	{
		Count = 0;
		Instructions = nullptr;
	}

	~CS_INSN_HOLDER()
	{
		cs_free(Instructions, Count);
	}
};

class CDisasmbler :
	protected CInstructionInfo
{
public:
	CDisasmbler(
		__in cs_mode mode,
		__in const char* comment,
		__in cs_arch arch,
		__in cs_opt_type optType,
		__in cs_opt_value optValue
		) : m_platform({arch, mode, nullptr, optType, optValue})
	{
		m_err = cs_open(m_platform.Arch, m_platform.Mode, &m_csh.Handle);
		if (m_err)
			return;

		if (m_platform.OptType)
			cs_option(m_csh.Handle, m_platform.OptType, m_platform.OptValue);
	}

	cs_err
	GetError()
	{
		return m_err;
	}

	__checkReturn
	std::unique_ptr<CS_INSN_HOLDER>
	Disasm(
		__in const void* code,
		__in size_t size,
		__in size_t baseAddr = 0
		)
	{
		std::unique_ptr<CS_INSN_HOLDER> i_holder(new CS_INSN_HOLDER(code, size));
		if (i_holder.get())
			i_holder->Count = cs_disasm_ex(m_csh.Handle, reinterpret_cast<const unsigned char*>(code), size, baseAddr, 0, &i_holder->Instructions);
		return i_holder;
	}

	void 
	PrintInstDetail(
		__in cs_insn& inst
		)
	{
		print_insn_detail(m_csh.Handle, m_platform.Mode, &inst);
	}

protected:
	CS_HANDLE m_csh;
	CS_PLATFORM m_platform;

	cs_err m_err;
};

class CDisasmbler64 :
	public CDisasmbler
{
public:
	CDisasmbler64(
		__in const char* comment = "X86 64 (Intel syntax)",
		__in cs_arch arch = cs_arch::CS_ARCH_X86,
		__in cs_opt_type optType = cs_opt_type::CS_OPT_DETAIL,
		__in cs_opt_value optValue = cs_opt_value::CS_OPT_ON
		) : CDisasmbler(cs_mode::CS_MODE_64, comment, arch, optType, optValue)
	{
	}
};
