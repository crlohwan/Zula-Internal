#pragma once
#include <d3dx9.h>
#include <thread>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "vector.hpp"
#include "xorenc.hpp"

typedef HRESULT( APIENTRY* Present ) ( IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA* );
Present oPresent = nullptr;

typedef HRESULT( APIENTRY* DrawIndexedPrimitive )( IDirect3DDevice9*, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT );
DrawIndexedPrimitive oDrawIndexedPrimitive = nullptr;

typedef BOOL( WINAPI* tBitBlt )( HDC, int, int, int, int, HDC, int, int, DWORD );
tBitBlt oBitBlt = nullptr;

typedef DWORD( *ent_next_0 )( DWORD );
ent_next_0 ent_next = ( ent_next_0 ) GetProcAddress( GetModuleHandleA( xorstr_( "acknex.dll" ) ), xorstr_( "ent_next" ) );

#define ZulaTeam (NumVertices == 1) || (NumVertices == 2) || (NumVertices == 3) || (NumVertices == 4)
#define GladioTeam (NumVertices == 5) || (NumVertices == 6) || (NumVertices == 7) || (NumVertices == 8)

#define isLocalPlayer strstr(sEntityHandle, xorstr_( "FPS_" )) && strstr(sEntityHandle, xorstr_( "_MESH.MDL" ))

#define ZulaModels strstr(sEntityHandle, xorstr_( "CHAR_HALIL" )) || strstr(sEntityHandle, xorstr_( "CHAR_CEMAL" )) || strstr(sEntityHandle, xorstr_( "CHAR_AZAD" )) || strstr(sEntityHandle, xorstr_( "CHAR_DAYI" )) || strstr(sEntityHandle, xorstr_( "CHAR_TAHIR" )) || strstr(sEntityHandle, xorstr_( "CHAR_CETIN" )) || strstr(sEntityHandle, xorstr_( "CHAR_SAMIL" )) || strstr(sEntityHandle, xorstr_( "CHAR_CUMALI" )) || strstr(sEntityHandle, xorstr_( "CHAR_POKADIN" )) || strstr(sEntityHandle, xorstr_( "CHAR_BAHRAM" )) || strstr(sEntityHandle, xorstr_( "CHAR_LEYLA" )) || strstr(sEntityHandle, xorstr_( "CHAR_OSMAN" )) || strstr(sEntityHandle, xorstr_( "CHAR_ALMANCI" )) || strstr(sEntityHandle, xorstr_( "CHAR_ADEM" )) || strstr(sEntityHandle, xorstr_( "CHAR_EVA" )) || strstr(sEntityHandle, xorstr_( "CHAR_SPIDER" ))
#define GladioModels strstr(sEntityHandle, xorstr_( "CHAR_AZER" )) || strstr(sEntityHandle, xorstr_( "CHAR_PIERRE" )) || strstr(sEntityHandle, xorstr_( "CHAR_BOB" )) || strstr(sEntityHandle, xorstr_( "CHAR_AVI" )) || strstr(sEntityHandle, xorstr_( "CHAR_EDWARD" )) || strstr(sEntityHandle, xorstr_( "CHAR_GEORGE" )) || strstr(sEntityHandle, xorstr_( "CHAR_IVAN" )) || strstr(sEntityHandle, xorstr_( "CHAR_JACK" )) || strstr(sEntityHandle, xorstr_( "CHAR_ROSA" )) || strstr(sEntityHandle, xorstr_( "CHAR_PABLO" )) || strstr(sEntityHandle, xorstr_( "CHAR_MILLA" )) || strstr(sEntityHandle, xorstr_( "CHAR_SALAH" )) || strstr(sEntityHandle, xorstr_( "CHAR_XENO" )) || strstr(sEntityHandle, xorstr_( "CHAR_KIERA" )) || strstr(sEntityHandle, xorstr_( "CHAR_ASYALI" )) || strstr(sEntityHandle, xorstr_( "CHAR_NANDA" )) || strstr(sEntityHandle, xorstr_( "CHAR_HAVVA" )) || strstr(sEntityHandle, xorstr_( "CHAR_SPIDERB" ))

#define GrenadeModels strstr(sEntityHandle, xorstr_( "SIL_BG_DUALK4_MESH" )) || strstr(sEntityHandle, xorstr_( "SIL_BS_TRP90_MESH" )) || strstr(sEntityHandle, xorstr_( "SIL_BF_M84_MESH" )) || strstr(sEntityHandle, xorstr_( "SIL_BG_M61_MESH" )) || strstr(sEntityHandle, xorstr_( "SIL_BG_C4KUMANDA_MESH" )) || strstr(sEntityHandle, xorstr_( "SIL_BG_MK3_MESH" )) || strstr(sEntityHandle, xorstr_( "SIL_BG_MK2_MESH" ))

namespace utils
{
    WNDPROC oWndProc = nullptr;

    bool menu = false;

    uintptr_t AcknexBase = ( uintptr_t ) GetModuleHandleA( xorstr_( "acknex.dll" ) );

    constexpr float x = 960.0f;
    constexpr float y = 540.0f;

    constexpr float yMin = 1080.0f;
    constexpr float size = 300.0f;

    ImColor linec( 0.0f, 1.0f, 0.0f, 1.0f );
    ImColor bombc( 1.0f, 0.0f, 0.0f, 1.0f );

    /*---------------------------------------*/

    bool WallHack = false; float bias = -0.5f;

    bool Chams = false;
    IDirect3DTexture9* texture = nullptr;

    bool EspBox = false;
    bool EspLine = false;
    bool EspGrenade = false;

    D3DXMATRIX temp{};

    bool EspDistance = false; DWORD LocalPlayer = 0;

    int team = 0; const char* teams[] = { "Zula", "Gladio" };

    /*---------------------------------------*/

    bool Aimbot = false; bool FovCircle = false;

    /*---------------------------------------*/

    bool NoRecoil = false; bool nrNopped = false;

    char* CNoRecoil = nullptr;

    BYTE nrOB[]  = { 0xDC, 0x8D, 0x60, 0x00, 0x00, 0x00 };
    BYTE nrOBn[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

    char pNoRecoil[] = "\xDC\x8D\x60\x00\x00\x00\xDD\x9D\x70\x00\x00\x00\xE8\x08\x00\x00\x00\x00\x00\x00";
    char mNoRecoil[] = "xxx???xxx???xx??????";

    /*---------------------------------------*/

    bool NoSpread = false; bool nsNopped = false;

    char* CNoSpread = nullptr;

    BYTE nsOB[]  = { 0xDD, 0x85, 0x98, 0x03, 0x00, 0x00 };
    BYTE nsOBn[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

    char pNoSpread[] = "\xDD\x85\x98\x03\x00\x00\xDC\x85\x90\x03\x00\x00\xDD\x9D\xA0\x03\x00\x00\xE8\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x90\x40\x58\xDD\x85\xA0\x03\x00\x00\xDC\x08\xDB\x9D\xA8\x03\x00\x00\x8B\x85\xA8\x03\x00\x00\x89\x85\xA0";
    char mNoSpread[] = "xxxx??xxxx??xxxx??xx?????????xxxxxxx??xxxxxx??xxxx??xxx";

    /*---------------------------------------*/

    bool NoSwitch = false; bool fsNopped = false;

    char* CNoSwitch = nullptr;

    BYTE fsOB[]  = { 0x8B, 0x85, 0x3C, 0x00, 0x00, 0x00 };
    BYTE fsOBn[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

    char pNoSwitch[] = "\x8B\x85\x3C\x00\x00\x00\x8B\x8D\x24\x12";
    char mNoSwitch[] = "xxx???xxxx";

    /*---------------------------------------*/

    bool NoSmoke = false;

    /*---------------------------------------*/

    bool SpeedLag = false;

    uint32_t c_trace = AcknexBase + 0x12080;

    BYTE ctOB[]  = { 0x8B, 0x54, 0x24, 0xC };
    BYTE ctOBn[] = { 0x90, 0x90, 0x90, 0x90 };

    /*---------------------------------------*/

    bool MegaJump = false;

    uint32_t setminmax = c_trace + 0x16;

    BYTE smOB[]  = { 0xE8, 0x45, 0xFE, 0xFF, 0xFF };
    BYTE smOBn[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

    /*---------------------------------------*/

    bool FastReload = false; bool frNopped = false;

    char* CFastReload = nullptr;

    BYTE frOB[]  = { 0x0A };
    BYTE frOBn[] = { 0x0B };

    char pFastReload[] = "\x0A\x83\xD0\x00\x89\x85\x34\x02\x00\x00\x8B\x85\x34\x02\x00\x00\x89";
    char mFastReload[] = "xxx?xxxx??xxxx??x";

    /*---------------------------------------*/

    bool FovChanger = false; bool fcNopped = false;

    char* CFovChanger = nullptr;

    BYTE fcOB[]  = { 0x0A };
    BYTE fcOBn[] = { 0x09 };

    char pFovChanger[] = "\x0A\x83\xD0\x00\x89\x85\x14\x01\x00\x00\x8B\x85\x14\x01\x00\x00\x8B\x95";
    char mFovChanger[] = "xxx?xxxx??xxxx??xx";

    /*---------------------------------------*/
}

HRESULT CreateSolidColorTexture( IDirect3DDevice9* pDevice, LPDIRECT3DTEXTURE9* texture, D3DCOLOR color )
{
    if ( FAILED( pDevice->CreateTexture( 1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, texture, nullptr ) ) )
        return E_FAIL;

    D3DLOCKED_RECT rect{};
    if ( FAILED( ( *texture )->LockRect( 0, &rect, nullptr, 0 ) ) )
        return E_FAIL;

    DWORD* pixel = ( DWORD* ) rect.pBits;

    if ( pixel == nullptr ) return E_FAIL;

    *pixel = color; ( *texture )->UnlockRect( 0 );

    return S_OK;
}

bool WriteMemory( uint32_t pTarget, LPCVOID buffer, SIZE_T size )
{
    DWORD oProtect = 0;

    if ( !VirtualProtect( ( LPVOID ) pTarget, size, PAGE_EXECUTE_READWRITE, &oProtect ) )
        return false;

    memcpy( ( void* ) pTarget, buffer, size );

    if ( !VirtualProtect( ( LPVOID ) pTarget, size, oProtect, &oProtect ) )
        return false;

    return true;
}

char* SearchPattern( char* base, SIZE_T size, char* pattern, char* mask )
{
    SIZE_T length = strlen( mask );

    for ( SIZE_T i = 0; i < size - length; i++ )
    {
        bool checker = true;

        for ( SIZE_T j = 0; j < length; j++ )
        {
            if ( mask[ j ] != '?' && pattern[ j ] != ( ( char* ) base )[ i + j ] )
            {
                checker = false;
                break;
            }
        }

        if ( checker ) return ( char* ) ( ( ULONG_PTR ) base + i );
    }

    return nullptr;
}

char* ScanProcessMemory( char* pattern, char* mask )
{
    MEMORY_BASIC_INFORMATION mbi{};

    char* stSearch = ( char* ) 0x20000000;
    char* enSearch = ( char* ) 0x80000000;

    while ( stSearch < enSearch )
    {
        if ( !VirtualQuery( stSearch, &mbi, sizeof( mbi ) ) )
        {
            stSearch += 0x1000;
            continue;
        }

        if ( mbi.State == MEM_COMMIT && ( mbi.Type == MEM_PRIVATE || mbi.Type == MEM_IMAGE ) )
        {
            DWORD oProtect = 0;

            if ( VirtualProtect(
                mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oProtect ) )
            {
                char* pLocation = SearchPattern( stSearch, mbi.RegionSize, pattern, mask );

                VirtualProtect( mbi.BaseAddress, mbi.RegionSize, oProtect, &oProtect );

                if ( pLocation ) return pLocation;
            }
        }

        stSearch += mbi.RegionSize;
    }

    return nullptr;
}

bool WorldToScreen( const Vector& pos, Vector& screen, const D3DXMATRIX& matrix )
{
    D3DXVECTOR4 clipCoords{};
    clipCoords.x = pos.x * matrix[ 0 ] + pos.y * matrix[ 4 ] + pos.z * matrix[ 8 ] + matrix[ 12 ];
    clipCoords.y = pos.x * matrix[ 1 ] + pos.y * matrix[ 5 ] + pos.z * matrix[ 9 ] + matrix[ 13 ];
    clipCoords.z = pos.x * matrix[ 2 ] + pos.y * matrix[ 6 ] + pos.z * matrix[ 10 ] + matrix[ 14 ];
    clipCoords.w = pos.x * matrix[ 3 ] + pos.y * matrix[ 7 ] + pos.z * matrix[ 11 ] + matrix[ 15 ];

    if ( clipCoords.w < 0.0f ) return false;

    D3DXVECTOR3 NDC{};
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = ( utils::x * NDC.x ) + utils::x;
    screen.y = ( utils::y * -NDC.y ) + utils::y;

    return true;
}

template <typename T>
T ReadMemory( DWORD pTarget )
{
    T buffer{}; buffer = *( T* ) pTarget;
    return buffer;
}

void LoopMatrix()
{
    uint32_t matViewProj = ReadMemory<uint32_t>(
        utils::AcknexBase + 0x243F8C
    );

    while ( true )
    {
        D3DXMATRIX Draw = ReadMemory<D3DXMATRIX>( matViewProj );

        if ( Draw._44 != 0.0f )
            utils::temp = Draw;
        else
            Draw = utils::temp;

        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }
}

void DrawLine( float x, float y, float w, float h, ImColor col ) noexcept
{
    ImGui::GetForegroundDrawList()->AddLine( ImVec2( x, y ), ImVec2( w, h ), col );
}

void DrawEspBox( Vector Head, Vector Foot ) noexcept
{
    Vector Box = Head - Foot;

    if ( Box.y < 0.0f ) Box.y = -Box.y;

    float w = Box.y * 0.5f; float x = Head.x - w * 0.5f;

    float wLine = Box.y * 0.15f; float hLine = Box.y * 0.30f;

    DrawLine( x, Head.y, x + wLine, Head.y, utils::linec );
    DrawLine( x, Head.y, x, Head.y + hLine, utils::linec );

    DrawLine( x + w, Head.y, x + w - wLine, Head.y, utils::linec );
    DrawLine( x + w, Head.y, x + w, Head.y + hLine, utils::linec );

    DrawLine( x, Head.y + Box.y, x + wLine, Head.y + Box.y, utils::linec );
    DrawLine( x, Head.y + Box.y, x, Head.y + Box.y - hLine, utils::linec );

    DrawLine( x + w, Head.y + Box.y, x + w - wLine, Head.y + Box.y, utils::linec );
    DrawLine( x + w, Head.y + Box.y, x + w, Head.y + Box.y - hLine, utils::linec );
}

void DrawEspLine( float w, float h ) noexcept
{
    DrawLine( utils::x, utils::yMin, w, h, utils::linec );
}

void DrawEspDistance( float x, float y, const char* tb ) noexcept
{
    ImGui::GetForegroundDrawList()->AddText( ImVec2( x , y ), utils::linec, tb );
}

void EntityProcessLoop()
{
    DWORD pEntity = ent_next( NULL );

    while ( pEntity )
    {
        pEntity = ent_next( pEntity );

        if ( pEntity != NULL )
        {
            DWORD dwEntityHandle = ReadMemory<DWORD>( pEntity + 0xC );

            if ( dwEntityHandle != NULL )
            {
                const char* sEntityHandle = ( const char* ) ( dwEntityHandle );

                if ( isLocalPlayer ) utils::LocalPlayer = pEntity;

                Vector pos = ReadMemory<Vector>( pEntity + 0x3DC );
                Vector screen; WorldToScreen( Vector( pos.x, pos.z, pos.y ), screen, utils::temp );

                if ( utils::EspBox || utils::EspLine || utils::EspDistance )
                {
                    if ( strstr( sEntityHandle, xorstr_( "CHAR_" ) ) && strstr( sEntityHandle, xorstr_( "_MESH.MDL" ) ) )
                    {
                        int isAlive = ReadMemory<int>( ReadMemory<DWORD>( ReadMemory<DWORD>( pEntity + 0x4 ) + 0x4 ) + 0x34 );

                        if ( isAlive == 67109120 )
                        {
                            Vector vHead, vFoot;

                            WorldToScreen( Vector( pos.x, pos.z + 32.0f, pos.y ), vHead, utils::temp );
                            WorldToScreen( Vector( pos.x, pos.z - 30.0f, pos.y ), vFoot, utils::temp );

                            Vector LocalPos = ReadMemory<Vector>( utils::LocalPlayer + 0x3DC );

                            float dist = LocalPos.DistTo( pos ) / 100.0f;

                            char xdist[ 64 ]{}; sprintf_s( xdist, xorstr_( "%.fm" ), dist );

                            if ( utils::EspBox )
                            {
                                if ( utils::team == 0 )
                                {
                                    if ( ZulaModels )
                                    {
                                        DrawEspBox( vHead, vFoot );
                                    }
                                }
                                else
                                {
                                    if ( GladioModels )
                                    {
                                        DrawEspBox( vHead, vFoot );
                                    }
                                }
                            }

                            if ( utils::EspLine )
                            {
                                if ( utils::team == 0 )
                                {
                                    if ( ZulaModels )
                                    {
                                        DrawEspLine( vFoot.x, vFoot.y );
                                    }
                                }
                                else
                                {
                                    if ( GladioModels )
                                    {
                                        DrawEspLine( vFoot.x, vFoot.y );
                                    }
                                }
                            }

                            if ( utils::EspDistance )
                            {
                                if ( utils::team == 0 )
                                {
                                    if ( ZulaModels )
                                    {
                                        DrawEspDistance( vFoot.x, vFoot.y, xdist );
                                    }
                                }
                                else
                                {
                                    if ( GladioModels )
                                    {
                                        DrawEspDistance( vFoot.x, vFoot.y, xdist );
                                    }
                                }
                            }
                        }
                    }
                }

                if ( utils::EspGrenade )
                {
                    if ( GrenadeModels )
                    {
                        ImGui::GetForegroundDrawList()->AddText(
                            ImVec2( screen.x, screen.y ), utils::bombc, xorstr_( "GRENADE" )
                        );
                    }
                }

                if ( utils::NoSmoke )
                {
                    if ( strstr(
                        sEntityHandle, xorstr_( "SMOKE" )
                    ) && strstr(
                        sEntityHandle, xorstr_( "SPRITE" )
                    ) && strstr(
                        sEntityHandle, xorstr_( ".DDS" )
                    ) )
                    {
                        *( Vector* ) ( pEntity + 0x3DC ) = { 999.0f, 999.0f, 999.0f };
                    }
                }
            }
        }
    }
}