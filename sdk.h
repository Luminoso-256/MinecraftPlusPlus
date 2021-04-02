#pragma once
namespace openGl {
	typedef void(__fastcall* glClear)();
	typedef void(__fastcall* glFlush)();
	typedef void(__fastcall* glEnable)();
	typedef void(__fastcall* glDisable)();
}

namespace user32 {
	typedef void(__fastcall* RedrawWindow)();
}