#include "D3D11RHI.h"


void UpdateBufferStats(ID3D11Buffer* Buffer, bool bAllocating)
{
    // D3D11_BUFFER_DESC Desc;
    // Buffer->GetDesc(&Desc);
    //
    // const bool bUniformBuffer = !!(Desc.BindFlags & D3D11_BIND_CONSTANT_BUFFER);
    // const bool bIndexBuffer = !!(Desc.BindFlags & D3D11_BIND_INDEX_BUFFER);
    // const bool bVertexBuffer = !!(Desc.BindFlags & D3D11_BIND_VERTEX_BUFFER);
    //
    // if (bAllocating)
    // {
    //     if (bUniformBuffer)
    //     {
    //         INC_MEMORY_STAT_BY(STAT_UniformBufferMemory,Desc.ByteWidth);
    //     }
    //     else if (bIndexBuffer)
    //     {
    //         INC_MEMORY_STAT_BY(STAT_IndexBufferMemory,Desc.ByteWidth);
    //     }
    //     else if (bVertexBuffer)
    //     {
    //         INC_MEMORY_STAT_BY(STAT_VertexBufferMemory,Desc.ByteWidth);
    //     }
    //     else
    //     {
    //         INC_MEMORY_STAT_BY(STAT_StructuredBufferMemory,Desc.ByteWidth);
    //     }
    // }
    // else
    // {
    //     if (bUniformBuffer)
    //     {
    //         DEC_MEMORY_STAT_BY(STAT_UniformBufferMemory,Desc.ByteWidth);
    //     }
    //     else if (bIndexBuffer)
    //     {
    //         DEC_MEMORY_STAT_BY(STAT_IndexBufferMemory,Desc.ByteWidth);
    //     }
    //     else if (bVertexBuffer)
    //     {
    //         DEC_MEMORY_STAT_BY(STAT_VertexBufferMemory,Desc.ByteWidth);
    //     }
    //     else
    //     {
    //         DEC_MEMORY_STAT_BY(STAT_StructuredBufferMemory,Desc.ByteWidth);
    //     }
    // }
}