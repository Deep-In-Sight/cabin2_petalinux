// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xgetphasemap.h"

extern XGetphasemap_Config XGetphasemap_ConfigTable[];

XGetphasemap_Config *XGetphasemap_LookupConfig(u16 DeviceId) {
	XGetphasemap_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XGETPHASEMAP_NUM_INSTANCES; Index++) {
		if (XGetphasemap_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XGetphasemap_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XGetphasemap_Initialize(XGetphasemap *InstancePtr, u16 DeviceId) {
	XGetphasemap_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XGetphasemap_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XGetphasemap_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

