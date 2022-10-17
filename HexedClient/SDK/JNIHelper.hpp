#pragma once
#include "../JNI/jni.h"

class JNIHelper
{
private:
	inline static jobject classloader_obj;
	inline static jmethodID findclass_md;

public:
	inline static JNIEnv* env;
	static jclass ForgeFindClass(const char*);
};