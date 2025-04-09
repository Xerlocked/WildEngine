#pragma once
#include "Templates/UnrealTypes.h"

class UEngineStatistics {
public:
	static uint32 GenUUID();

private:
	static uint32 NextUUID;
};