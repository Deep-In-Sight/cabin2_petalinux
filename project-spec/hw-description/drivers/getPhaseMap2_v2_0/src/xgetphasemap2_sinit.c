// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xgetphasemap2.h"

extern XGetphasemap2_Config XGetphasemap2_ConfigTable[];

XGetphasemap2_Config *XGetphasemap2_LookupConfig(u16 DeviceId) {
	XGetphasemap2_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XGETPHASEMAP2_NUM_INSTANCES; Index++) {
		if (XGetphasemap2_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XGetphasemap2_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XGetphasemap2_Initialize(XGetphasemap2 *InstancePtr, u16 DeviceId) {
	XGetphasemap2_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XGetphasemap2_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XGetphasemap2_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

