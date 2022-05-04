// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XGETPHASEMAP2_H
#define XGETPHASEMAP2_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xgetphasemap2_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XGetphasemap2_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XGetphasemap2;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XGetphasemap2_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XGetphasemap2_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XGetphasemap2_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XGetphasemap2_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XGetphasemap2_Initialize(XGetphasemap2 *InstancePtr, u16 DeviceId);
XGetphasemap2_Config* XGetphasemap2_LookupConfig(u16 DeviceId);
int XGetphasemap2_CfgInitialize(XGetphasemap2 *InstancePtr, XGetphasemap2_Config *ConfigPtr);
#else
int XGetphasemap2_Initialize(XGetphasemap2 *InstancePtr, const char* InstanceName);
int XGetphasemap2_Release(XGetphasemap2 *InstancePtr);
#endif

void XGetphasemap2_Start(XGetphasemap2 *InstancePtr);
u32 XGetphasemap2_IsDone(XGetphasemap2 *InstancePtr);
u32 XGetphasemap2_IsIdle(XGetphasemap2 *InstancePtr);
u32 XGetphasemap2_IsReady(XGetphasemap2 *InstancePtr);
void XGetphasemap2_EnableAutoRestart(XGetphasemap2 *InstancePtr);
void XGetphasemap2_DisableAutoRestart(XGetphasemap2 *InstancePtr);

void XGetphasemap2_Set_regCtrl(XGetphasemap2 *InstancePtr, u32 Data);
u32 XGetphasemap2_Get_regCtrl(XGetphasemap2 *InstancePtr);
void XGetphasemap2_Set_port0_offset(XGetphasemap2 *InstancePtr, u32 Data);
u32 XGetphasemap2_Get_port0_offset(XGetphasemap2 *InstancePtr);
void XGetphasemap2_Set_port1_offset(XGetphasemap2 *InstancePtr, u32 Data);
u32 XGetphasemap2_Get_port1_offset(XGetphasemap2 *InstancePtr);

void XGetphasemap2_InterruptGlobalEnable(XGetphasemap2 *InstancePtr);
void XGetphasemap2_InterruptGlobalDisable(XGetphasemap2 *InstancePtr);
void XGetphasemap2_InterruptEnable(XGetphasemap2 *InstancePtr, u32 Mask);
void XGetphasemap2_InterruptDisable(XGetphasemap2 *InstancePtr, u32 Mask);
void XGetphasemap2_InterruptClear(XGetphasemap2 *InstancePtr, u32 Mask);
u32 XGetphasemap2_InterruptGetEnabled(XGetphasemap2 *InstancePtr);
u32 XGetphasemap2_InterruptGetStatus(XGetphasemap2 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
