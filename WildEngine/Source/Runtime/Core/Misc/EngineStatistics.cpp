#include "EngineStatistics.h"

uint32 UEngineStatistics::NextUUID = 1;

uint32 UEngineStatistics::GenUUID()
{
	return NextUUID++;
}
