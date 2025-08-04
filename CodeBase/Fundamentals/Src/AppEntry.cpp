#include"Global_Header.h"

using namespace std;
using namespace DirectX;

// Globals
IDXGISwapChain* g_SwapChain = nullptr;
ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_Context = nullptr;
ID3D11RenderTargetView* g_RenderTargetView = nullptr;

ID3D11InputLayout* g_InputLayout = nullptr;
ID3D11Buffer* g_VertexBuffer = nullptr;
ID3D11VertexShader* g_VertexShader = nullptr;
ID3D11PixelShader* g_PixelShader = nullptr;

// Simple vertex structure
struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT4 color;
};

// Forward declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hwnd);
void CleanupD3D();
void RenderFrame();
HRESULT InitPipeline();

// HLSL shader code as strings (you can also compile offline)
const char* g_VS_ShaderCode =
"struct VS_INPUT                          \n"
"{                                       \n"
"    float3 pos : POSITION;               \n"
"    float4 col : COLOR;                  \n"
"};                                      \n"
"                                        \n"
"struct PS_INPUT                         \n"
"{                                       \n"
"    float4 pos : SV_POSITION;           \n"
"    float4 col : COLOR;                  \n"
"};                                      \n"
"                                        \n"
"PS_INPUT main(VS_INPUT input)           \n"
"{                                       \n"
"    PS_INPUT output;                     \n"
"    output.pos = float4(input.pos, 1.0);\n"
"    output.col = input.col;              \n"
"    return output;                       \n"
"}                                       \n";

const char* g_PS_ShaderCode =
"float4 main(float4 pos : SV_POSITION, float4 col : COLOR) : SV_TARGET\n"
"{                                                                   \n"
"    return col;                                                     \n"
"}                                                                   \n";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"DX11TriangleWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"DirectX 11 Red Triangle",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);

    if (FAILED(InitD3D(hwnd)))
    {
        MessageBox(hwnd, L"Failed to initialize Direct3D 11", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    if (FAILED(InitPipeline()))
    {
        MessageBox(hwnd, L"Failed to initialize pipeline", L"Error", MB_OK | MB_ICONERROR);
        CleanupD3D();
        return 0;
    }

    // Main message loop with rendering
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            RenderFrame();
        }
    }

    CleanupD3D();
    return (int)msg.wParam;
}

HRESULT InitD3D(HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr, 0,
        D3D11_SDK_VERSION,
        &scd,
        &g_SwapChain,
        &g_Device,
        nullptr,
        &g_Context);

    if (FAILED(hr))
        return hr;

    ID3D11Texture2D* backBuffer = nullptr;
    hr = g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (FAILED(hr))
        return hr;

    hr = g_Device->CreateRenderTargetView(backBuffer, nullptr, &g_RenderTargetView);
    backBuffer->Release();
    if (FAILED(hr))
        return hr;

    g_Context->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);

    RECT rc;
    GetClientRect(hwnd, &rc);
    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<float>(rc.right - rc.left);
    vp.Height = static_cast<float>(rc.bottom - rc.top);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    g_Context->RSSetViewports(1, &vp);

    return S_OK;
}

HRESULT InitPipeline()
{
    HRESULT hr;

    // Compile vertex shader
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    hr = D3DCompile(g_VS_ShaderCode, strlen(g_VS_ShaderCode), nullptr, nullptr, nullptr,
        "main", "vs_4_0", 0, 0, &vsBlob, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        return hr;
    }

    hr = g_Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &g_VertexShader);
    if (FAILED(hr))
    {
        vsBlob->Release();
        return hr;
    }

    // Define input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color),    D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    hr = g_Device->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &g_InputLayout);
    vsBlob->Release();
    if (FAILED(hr))
        return hr;

    g_Context->IASetInputLayout(g_InputLayout);

    // Compile pixel shader
    ID3DBlob* psBlob = nullptr;
    hr = D3DCompile(g_PS_ShaderCode, strlen(g_PS_ShaderCode), nullptr, nullptr, nullptr,
        "main", "ps_4_0", 0, 0, &psBlob, &errorBlob);
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        return hr;
    }

    hr = g_Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &g_PixelShader);
    psBlob->Release();
    if (FAILED(hr))
        return hr;

    // Create vertex buffer
    Vertex vertices[] =
    {
        { XMFLOAT3(0.0f,  0.5f, 0.0f), XMFLOAT4(1, 0, 0, 1) }, // top, red
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(1, 0, 0, 1) }, // right, red
        { XMFLOAT3(-0.5f,-0.5f, 0.0f), XMFLOAT4(1, 0, 0, 1) }, // left, red
    };

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * 3;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices;

    hr = g_Device->CreateBuffer(&bd, &initData, &g_VertexBuffer);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void RenderFrame()
{
    // Clear to cornflower blue background
    float clearColor[4] = { 0.392f, 0.584f, 0.929f, 1.0f };
    g_Context->ClearRenderTargetView(g_RenderTargetView, clearColor);

    // Set vertex buffer
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_Context->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

    // Set primitive topology
    g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Set shaders
    g_Context->VSSetShader(g_VertexShader, nullptr, 0);
    g_Context->PSSetShader(g_PixelShader, nullptr, 0);

    // Draw 3 vertices = one triangle
    g_Context->Draw(3, 0);

    // Present
    g_SwapChain->Present(1, 0);
}

void CleanupD3D()
{
    if (g_VertexBuffer) { g_VertexBuffer->Release(); g_VertexBuffer = nullptr; }
    if (g_InputLayout) { g_InputLayout->Release(); g_InputLayout = nullptr; }
    if (g_VertexShader) { g_VertexShader->Release(); g_VertexShader = nullptr; }
    if (g_PixelShader) { g_PixelShader->Release(); g_PixelShader = nullptr; }
    if (g_RenderTargetView) { g_RenderTargetView->Release(); g_RenderTargetView = nullptr; }
    if (g_SwapChain) { g_SwapChain->Release(); g_SwapChain = nullptr; }
    if (g_Context) { g_Context->Release(); g_Context = nullptr; }
    if (g_Device) { g_Device->Release(); g_Device = nullptr; }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
