// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xgetphasemap2.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XGetphasemap2_CfgInitialize(XGetphasemap2 *InstancePtr, XGetphasemap2_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XGetphasemap2_Start(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL) & 0x80;
    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XGetphasemap2_IsDone(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XGetphasemap2_IsIdle(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XGetphasemap2_IsReady(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XGetphasemap2_EnableAutoRestart(XGetphasemap2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XGetphasemap2_DisableAutoRestart(XGetphasemap2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_AP_CTRL, 0);
}

void XGetphasemap2_Set_regCtrl(XGetphasemap2 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_REGCTRL_DATA, Data);
}

u32 XGetphasemap2_Get_regCtrl(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_REGCTRL_DATA);
    return Data;
}

void XGetphasemap2_Set_port0_offset(XGetphasemap2 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_PORT0_OFFSET_DATA, Data);
}

u32 XGetphasemap2_Get_port0_offset(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_PORT0_OFFSET_DATA);
    return Data;
}

void XGetphasemap2_Set_port1_offset(XGetphasemap2 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_PORT1_OFFSET_DATA, Data);
}

u32 XGetphasemap2_Get_port1_offset(XGetphasemap2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_PORT1_OFFSET_DATA);
    return Data;
}

void XGetphasemap2_InterruptGlobalEnable(XGetphasemap2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_GIE, 1);
}

void XGetphasemap2_InterruptGlobalDisable(XGetphasemap2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_GIE, 0);
}

void XGetphasemap2_InterruptEnable(XGetphasemap2 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_IER);
    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_IER, Register | Mask);
}

void XGetphasemap2_InterruptDisable(XGetphasemap2 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_IER);
    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_IER, Register & (~Mask));
}

void XGetphasemap2_InterruptClear(XGetphasemap2 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetphasemap2_WriteReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_ISR, Mask);
}

u32 XGetphasemap2_InterruptGetEnabled(XGetphasemap2 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_IER);
}

u32 XGetphasemap2_InterruptGetStatus(XGetphasemap2 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGetphasemap2_ReadReg(InstancePtr->Control_BaseAddress, XGETPHASEMAP2_CONTROL_ADDR_ISR);
}

