#pragma once

class Patching
{
private:
	static void PatchOnUpdate();
	static void PatchSetSprinting();
	static void PatchSwapBuffers();

public:
	static void ApplyPatches();
	static void UnapplyPatches();
};
