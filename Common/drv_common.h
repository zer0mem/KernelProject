/**
 * @file drv_common.h
 * @author created by: Peter Hlavaty
 *
 * Variables likely to change, have to be excluded, and obtained as param fron ring3 [windbg pykd parser]
 *
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <ntifs.h>
#include <wdm.h>

#include <Common/kernel/CppDriver.h>

#include <utility>
using CID = std::pair<HANDLE, HANDLE>;//pid, tid

const size_t g_cMaxLocalStringLength = 0x100;

#endif //__DRV_COMMON_H__
