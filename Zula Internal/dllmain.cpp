#include <d3dx9.h>
#include <thread>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "detours.h"
#include "xorenc.hpp"
#include "functions.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( utils::menu && ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) ) return true;

	return CallWindowProcA( utils::oWndProc, hWnd, msg, wParam, lParam );
}

HRESULT __stdcall hkPresent( IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion )
{
	static bool init = true;

	if ( init )
	{
		D3DDEVICE_CREATION_PARAMETERS d3dcp{};
		pDevice->GetCreationParameters( &d3dcp );

		if ( d3dcp.hFocusWindow != nullptr )
		{
			utils::oWndProc = ( WNDPROC ) SetWindowLongA(
				d3dcp.hFocusWindow, GWLP_WNDPROC, ( LONG_PTR ) WndProc
			);

			ImGui::CreateContext();
			ImGui::StyleColorsLight();
			ImGui_ImplWin32_Init( d3dcp.hFocusWindow );
			ImGui_ImplDX9_Init( pDevice );

			std::thread( LoopMatrix ).detach();

			CreateSolidColorTexture( pDevice,
			&utils::texture, D3DCOLOR_ARGB( 255, 255, 0, 0 ) );
		}

		init = false;
	}

	if ( GetAsyncKeyState( VK_INSERT ) & 1 )
		utils::menu = !utils::menu;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if ( utils::menu )
	{
		ImGui::SetNextWindowSize( ImVec2( 300.0f, 300.0f ) );

		ImGui::Begin( xorstr_( "crlohwan" ), &utils::menu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );

		if ( ImGui::CollapsingHeader( xorstr_( "Visuals" ) ) )
		{
			ImGui::Checkbox( xorstr_( "WallHack" ), &utils::WallHack );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Esp Box" ), &utils::EspBox );
			ImGui::Checkbox( xorstr_( "Chams" ), &utils::Chams );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Esp Line" ), &utils::EspLine );
			ImGui::Checkbox( xorstr_( "Esp Grenade" ), &utils::EspGrenade );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Esp Distance" ), &utils::EspDistance );
		}

		if ( ImGui::CollapsingHeader( xorstr_( "Aim Assist" ) ) )
		{
			ImGui::Checkbox( xorstr_( "Aimbot" ), &utils::Aimbot );
			ImGui::Checkbox( xorstr_( "FoV Circle" ), &utils::FovCircle );
		}

		if ( ImGui::CollapsingHeader( xorstr_( "Memory" ) ) )
		{
			ImGui::Checkbox( xorstr_( "No Recoil" ), &utils::NoRecoil );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Speed Lag" ), &utils::SpeedLag );
			ImGui::Checkbox( xorstr_( "No Spread" ), &utils::NoSpread );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Mega Jump" ), &utils::MegaJump );
			ImGui::Checkbox( xorstr_( "No Switch" ), &utils::NoSwitch );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Fast Reload" ), &utils::FastReload );
			ImGui::Checkbox( xorstr_( "No Smoke " ), &utils::NoSmoke );
			ImGui::SameLine(); ImGui::Checkbox( xorstr_( "Fov Changer" ), &utils::FovChanger );
		}

		if ( ImGui::CollapsingHeader( xorstr_( "Settings" ) ) )
		{
			ImGui::ColorEdit4( xorstr_( "Line" ), ( float* )&utils::linec, ImGuiColorEditFlags_PickerHueWheel );
			ImGui::ColorEdit4( xorstr_( "Bomb" ), ( float* )&utils::bombc, ImGuiColorEditFlags_PickerHueWheel );
			ImGui::Combo( xorstr_( "Team" ), &utils::team, utils::teams, IM_ARRAYSIZE( utils::teams ) );
		}

		ImGui::End();
	}

	EntityProcessLoop();

	if ( utils::FovCircle )
	{
		ImGui::GetBackgroundDrawList()->AddCircle(
			ImVec2( utils::x, utils::y ), utils::size, utils::linec, 100
		);
	}

	if ( utils::NoRecoil )
	{
		if ( !utils::nrNopped )
		{
			utils::CNoRecoil = ScanProcessMemory(
				utils::pNoRecoil, utils::mNoRecoil );

			WriteMemory(
				( uint32_t ) utils::CNoRecoil,
				&utils::nrOBn, sizeof( utils::nrOBn ) );

			utils::nrNopped = true;
		}
	}
	else
	{
		if ( utils::nrNopped )
		{
			WriteMemory(
				( uint32_t ) utils::CNoRecoil,
				&utils::nrOB, sizeof( utils::nrOB ) );

			utils::nrNopped = false;
		}
	}

	if ( utils::NoSpread )
	{
		if ( !utils::nsNopped )
		{
			utils::CNoSpread = ScanProcessMemory(
				utils::pNoSpread, utils::mNoSpread );

			WriteMemory(
				( uint32_t ) utils::CNoSpread,
				&utils::nsOBn, sizeof( utils::nsOBn ) );

			utils::nsNopped = true;
		}
	}
	else
	{
		if ( utils::nsNopped )
		{
			WriteMemory(
				( uint32_t ) utils::CNoSpread,
				&utils::nsOB, sizeof( utils::nsOB ) );

			utils::nsNopped = false;
		}
	}

	if ( utils::NoSwitch )
	{
		if ( !utils::fsNopped )
		{
			utils::CNoSwitch = ScanProcessMemory(
				utils::pNoSwitch, utils::mNoSwitch );

			WriteMemory(
				( uint32_t ) utils::CNoSwitch,
				&utils::fsOBn, sizeof( utils::fsOBn ) );

			utils::fsNopped = true;
		}
	}
	else
	{
		if ( utils::fsNopped )
		{
			WriteMemory(
				( uint32_t ) utils::CNoSwitch,
				&utils::fsOB, sizeof( utils::fsOB ) );

			utils::fsNopped = false;
		}
	}

	if ( utils::SpeedLag )
	{
		static bool isNopped = false;

		if ( GetAsyncKeyState( 0x46 ) )
		{
			if ( !isNopped )
			{
				WriteMemory(
					utils::c_trace,
					&utils::ctOBn, sizeof( utils::ctOBn ) );

				isNopped = true;
			}
		}
		else
		{
			if ( isNopped )
			{
				WriteMemory(
					utils::c_trace,
					&utils::ctOB, sizeof( utils::ctOB ) );

				isNopped = false;
			}
		}
	}

	if ( utils::MegaJump )
	{
		static bool isNopped = false;

		if ( GetAsyncKeyState( VK_SPACE ) )
		{
			if ( !isNopped )
			{
				WriteMemory(
					utils::setminmax,
					&utils::smOBn, sizeof( utils::smOBn ) );

				isNopped = true;
			}
		}
		else
		{
			if ( isNopped )
			{
				WriteMemory(
					utils::setminmax,
					&utils::smOB, sizeof( utils::smOB ) );

				isNopped = false;
			}
		}
	}

	if ( utils::FastReload )
	{
		if ( !utils::frNopped )
		{
			utils::CFastReload = ScanProcessMemory(
				utils::pFastReload, utils::mFastReload );

			WriteMemory(
				( uint32_t ) utils::CFastReload,
				&utils::frOBn, sizeof( utils::frOBn ) );

			utils::frNopped = true;
		}
	}
	else
	{
		if ( utils::frNopped )
		{
			WriteMemory(
				( uint32_t ) utils::CFastReload,
				&utils::frOB, sizeof( utils::frOB ) );

			utils::frNopped = false;
		}
	}

	if ( utils::FovChanger )
	{
		if ( !utils::fcNopped )
		{
			utils::CFovChanger = ScanProcessMemory(
				utils::pFovChanger, utils::mFovChanger );

			WriteMemory(
				( uint32_t ) utils::CFovChanger,
				&utils::fcOBn, sizeof( utils::fcOBn ) );

			utils::fcNopped = true;
		}
	}
	else
	{
		if ( utils::fcNopped )
		{
			WriteMemory(
				( uint32_t ) utils::CFovChanger,
				&utils::fcOB, sizeof( utils::fcOB ) );

			utils::fcNopped = false;
		}
	}

	ImGui::GetIO().MouseDrawCursor = utils::menu;
	ImGui::EndFrame(); ImGui::Render();
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );

	return oPresent( pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

HRESULT __stdcall hkDrawIndexedPrimitive( IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE unnamedParam1, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount )
{
	if ( utils::WallHack )
	{
		if ( utils::team == 0 )
		{
			if ( ZulaTeam )
			{
				pDevice->SetRenderState( D3DRS_DEPTHBIAS, *( DWORD* ) &utils::bias );
				oDrawIndexedPrimitive( pDevice, unnamedParam1, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				pDevice->SetRenderState( D3DRS_DEPTHBIAS, 0 );
			}
		}
		else
		{
			if ( GladioTeam )
			{
				pDevice->SetRenderState( D3DRS_DEPTHBIAS, *( DWORD* ) &utils::bias );
				oDrawIndexedPrimitive( pDevice, unnamedParam1, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				pDevice->SetRenderState( D3DRS_DEPTHBIAS, 0 );
			}
		}
	}

	if ( utils::Chams )
	{
		if ( utils::team == 0 )
		{
			if ( ZulaTeam )
			{
				pDevice->SetRenderState( D3DRS_ZENABLE, 0 ); pDevice->SetTexture( 0, utils::texture );
				oDrawIndexedPrimitive( pDevice, unnamedParam1, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				pDevice->SetRenderState( D3DRS_ZENABLE, 1 ); pDevice->SetTexture( 0, utils::texture );
			}
		}
		else
		{
			if ( GladioTeam )
			{
				pDevice->SetRenderState( D3DRS_ZENABLE, 0 ); pDevice->SetTexture( 0, utils::texture );
				oDrawIndexedPrimitive( pDevice, unnamedParam1, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				pDevice->SetRenderState( D3DRS_ZENABLE, 1 ); pDevice->SetTexture( 0, utils::texture );
			}
		}
	}

	return oDrawIndexedPrimitive( pDevice, unnamedParam1, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
}

BOOL __stdcall hkBitBlt( HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop )
{
	utils::menu = false;

	utils::WallHack = false; utils::EspBox = false;
	utils::Chams = false; utils::EspLine = false;
	utils::EspGrenade = false; utils::FovCircle = false;

	return oBitBlt( hdc, x, y, cx, cy, hdcSrc, x1, y1, rop );
}

HMODULE hMod = nullptr;

static void InitHook()
{
	while ( !GetModuleHandleA( xorstr_( "d3d9.dll" ) ) ) {
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}

	HWND hWnd = CreateWindowA( "BUTTON", "DX", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, hMod, nullptr );
	if ( hWnd == nullptr ) return;

	IDirect3D9* d3d = Direct3DCreate9( D3D_SDK_VERSION );

	if ( d3d == nullptr )
	{
		DestroyWindow( hWnd );
		return;
	}

	D3DPRESENT_PARAMETERS d3dpp{};
	RtlZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;

	IDirect3DDevice9* d3ddev = nullptr;
	HRESULT hr = d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev );
	if ( FAILED( hr ) )
	{
		d3d->Release();
		DestroyWindow( hWnd );
		return;
	}

	DWORD* dVtable = ( DWORD* ) d3ddev;
	dVtable = ( DWORD* ) dVtable[ 0 ];

	oPresent = ( Present ) dVtable[ 17 ];
	oDrawIndexedPrimitive = ( DrawIndexedPrimitive ) dVtable[ 82 ];
	oBitBlt = ( tBitBlt ) GetProcAddress( GetModuleHandleA( xorstr_( "gdi32.dll" ) ), xorstr_( "BitBlt" ) );

	DetourTransactionBegin();
	DetourUpdateThread( GetCurrentThread() );
	DetourAttach( &( PVOID& ) oPresent, hkPresent );
	DetourAttach( &( PVOID& ) oDrawIndexedPrimitive, hkDrawIndexedPrimitive );
	DetourAttach( &( PVOID& ) oBitBlt, hkBitBlt );
	DetourTransactionCommit();

	d3ddev->Release();
	d3d->Release();
	DestroyWindow( hWnd );
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	UNREFERENCED_PARAMETER( lpReserved );

	switch ( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		hMod = hModule;
		DisableThreadLibraryCalls( hModule );
		CreateThread( nullptr, 0, ( LPTHREAD_START_ROUTINE ) InitHook, nullptr, 0, nullptr );
		break;
	}

	return TRUE;
}