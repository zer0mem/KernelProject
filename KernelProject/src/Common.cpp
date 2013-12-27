/**
 * @file Common.cpp
 * @author created by: Peter Hlavaty
 * @author \n
 * @author Copyright (c) 2013 ESET, spol. s r. o.
 * @note current owner: Peter Hlavaty (peter.hlavaty@eset.sk)
 * @note IMPORTANT: Before doing any significant change to this file check your plan with the current owner to avoid unexpected behaviour.
 */

#include "Common.h"
#include "drv_common.h"

#include "../../Common/Kernel/IRQL.hpp"
#include "../../Common/Kernel/MemoryMapping.h"
#include "../../Common/utils/Undoc.hpp"

void EnviromentDependentVariablesInit()
{
	//win8 CP; x64
	CUndoc::Init(
		VADVadRoot,
		VADAddressCreationLock,
		VADWorkingSetMutex,
		VADFlags,
		VADSameThreadApcFlags,
		0x090,// TrapFrame : Ptr64 _KTRAP_FRAME
		offsetof(_MM_AVL_TABLE, BalancedRoot),
		offsetof(_MM_AVL_TABLE, AvlInfo),
		(~0x3),
		(offsetof(_MMVAD_SHORT, VadNode) + offsetof(_MM_AVL_NODE, Parent)), 
		(offsetof(_MMVAD_SHORT, VadNode) + offsetof(_MM_AVL_NODE, LeftChild)), 
		(offsetof(_MMVAD_SHORT, VadNode) + offsetof(_MM_AVL_NODE, RightChild)),
		offsetof(_MMVAD_SHORT, StartingVpn), 
		offsetof(_MMVAD_SHORT, EndingVpn),
		offsetof(_MMVAD_SHORT, Flags),
		0xE0C,
		0x1478,		
		0x330,
		0x7D0,
		0x7010008004002001
		);
}
