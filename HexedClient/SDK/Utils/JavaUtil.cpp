#include "JavaUtil.hpp"

jclass JavaUtil::GetArrayListClass()
{
	if (ArrayListClass == NULL) ArrayListClass = JNIHelper::env->FindClass("java/util/ArrayList");
	return ArrayListClass;
}

jclass JavaUtil::GetListClass()
{
	if (ListClass == NULL) ListClass = JNIHelper::env->FindClass("java/util/List");
	return ListClass;
}

jint JavaUtil::GetArraySize(jobject obj)
{
	if (GetArrayListClass() == NULL) return NULL;

	if (ArrayListSizeField == NULL)
	{
		ArrayListSizeField = JNIHelper::env->GetFieldID(GetArrayListClass(), "size", "I");
		if (ArrayListSizeField == NULL) return NULL;
	}

	return JNIHelper::env->GetIntField(obj, ArrayListSizeField);
}

jobjectArray JavaUtil::GetArray(jobject obj)
{
	if (GetArrayListClass() == NULL) return NULL;

	if (ArrayListElementDataField == NULL)
	{
		ArrayListElementDataField = JNIHelper::env->GetFieldID(GetArrayListClass(), "elementData", "[Ljava/lang/Object;");
		if (ArrayListElementDataField == NULL) return NULL;
	}

	return (jobjectArray)JNIHelper::env->GetObjectField(obj, ArrayListElementDataField);
}