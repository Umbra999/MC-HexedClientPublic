#pragma once
#include "../JNI/jni.h"

class JNIHelper
{
private:
	inline static jclass LaunchWrapperClassLoaderClass;
	inline static jmethodID FindClassMethodID;
	inline static jclass LaunchClass;
	inline static jfieldID ClassLoaderFieldID;
	inline static jobject ClassLoaderObject;

public:
	inline static JNIEnv* env;
	static jclass ForgeFindClass(const char*);
};