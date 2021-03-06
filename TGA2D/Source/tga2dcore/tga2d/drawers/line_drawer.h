#pragma once
#include <tga2d/render/render_common.h>
#include <tga2d/shaders/Shader.h>

namespace Tga2D
{
    class CRenderObjectLine;
    class CDirectEngine;
    class CLineDrawer : public CShader
    {
    public:
        CLineDrawer(CEngine* anEngine);
        ~CLineDrawer();
        bool Init() override;
        void Draw(CRenderObjectLine* aObject);
		void Draw(CLineMultiPrimitive* aObject);
    private:
        CLineDrawer &operator =( const CLineDrawer &anOther ) = delete;
        bool CreateInputLayout(ID3D10Blob* aVS) override;
        bool InitShaders();
        void CreateBuffer();

        void SetShaderParameters(CRenderObjectLine* aObject);
        void UpdateVertexes(CRenderObjectLine* aObject);
        ComPtr<ID3D11Buffer> myVertexBuffer;
        SSimpleVertex myVertices[2] = {{},{}};
        CDirectEngine& myEngine;
    };
}