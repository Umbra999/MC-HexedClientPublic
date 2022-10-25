#pragma once
#include "../JNIHelper.hpp"

class JavaUtil
{
private:
	inline static jclass ArrayListClass = NULL;
	inline static jclass ListClass = NULL;

	inline static jfieldID ArrayListElementDataField = NULL;
	inline static jfieldID ArrayListSizeField = NULL;

	static jclass GetArrayListClass();
	static jclass GetListClass();

public:
	static jint GetArraySize(jobject);
	static jobjectArray GetArray(jobject);
};