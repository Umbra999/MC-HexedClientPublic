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

jfieldID JavaUtil::GetArrayListElementDataField()
{
	if (GetArrayListClass() == NULL) return NULL;
	if (ArrayListElementDataField == NULL) ArrayListElementDataField = JNIHelper::env->GetFieldID(GetArrayListClass(), "elementData", "[Ljava/lang/Object;");
	return ArrayListElementDataField;
}

jfieldID JavaUtil::GetArrayListSizeField()
{
	if (GetArrayListClass() == NULL) return NULL;
	if (ArrayListSizeField == NULL) ArrayListSizeField = JNIHelper::env->GetFieldID(GetArrayListClass(), "size", "I");
	return ArrayListSizeField;
}

jint JavaUtil::GetArraySize(jobject obj)
{
	if (GetArrayListSizeField() == NULL) return NULL;
	return JNIHelper::env->GetIntField(obj, JavaUtil::GetArrayListSizeField());
}

jobjectArray JavaUtil::GetArray(jobject obj)
{
	if (GetArrayListElementDataField() == NULL) return NULL;
	return (jobjectArray)JNIHelper::env->GetObjectField(obj, JavaUtil::GetArrayListElementDataField());
}