/*
 * Copyright 2020 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrD3DRootSignature_DEFINED
#define GrD3DRootSignature_DEFINED

#include "include/gpu/d3d/GrD3DTypes.h"
#include "src/gpu/GrManagedResource.h"

class GrD3DGpu;

class GrD3DRootSignature : public GrManagedResource {
public:
    static sk_sp<GrD3DRootSignature> Make(GrD3DGpu* gpu, int numTextureSamplers);

    bool isCompatible(int numTextureSamplers) const;

    ID3D12RootSignature* rootSignature() const { return fRootSignature.get(); }

#ifdef SK_TRACE_MANAGED_RESOURCES
    /** Output a human-readable dump of this resource's information
    */
    void dumpInfo() const override {
        SkDebugf("GrD3DRootSignature: %p, numTextures: %d (%d refs)\n",
                 fRootSignature.get(), fNumTextureSamplers, this->getRefCnt());
    }
#endif

private:
    GrD3DRootSignature(gr_cp<ID3D12RootSignature> rootSig, int numTextureSamplers);

    void freeGPUData() const override;

    // mutable needed so we can release the resource in freeGPUData
    mutable gr_cp<ID3D12RootSignature> fRootSignature;
    int fNumTextureSamplers;
};

#endif