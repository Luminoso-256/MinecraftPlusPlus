#pragma once

//all hooked functions from opengl32
namespace openGl {
	typedef void(__fastcall* glClear)();
	typedef void(__fastcall* glFlush)();
	typedef void(__fastcall* glEnable)();
	typedef void(__fastcall* glDisable)();
}

//all hooked functions from user32
namespace user32 {
	//called every frame
	typedef void(__fastcall* RedrawWindow)();
	//input
	typedef SHORT(__fastcall* GetKeyState)(int nVirtKey);
}

//Things from the main minecraftplus module

//we are  able to hardcode like this ignoring the offset because of the exe's OptionalHeader.AddressOfEntryPoint symbol, which means that it loads into the same memory location every time.

namespace MinecraftPlus {
	const unsigned long long mainLoopAddress = 0x00007FF6FA061DB0;
	typedef void(__fastcall* mainLoop)();
}