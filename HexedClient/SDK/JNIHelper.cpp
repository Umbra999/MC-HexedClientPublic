#include "JNIHelper.hpp"

jclass JNIHelper::ForgeFindClass(const char* name)
{
	if (LaunchWrapperClassLoaderClass == NULL)
	{
		LaunchWrapperClassLoaderClass = JNIHelper::env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
		if (LaunchWrapperClassLoaderClass == NULL) return NULL;
	}

	if (FindClassMethodID == NULL)
	{
		FindClassMethodID = JNIHelper::env->GetMethodID(LaunchWrapperClassLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		if (FindClassMethodID == NULL) return NULL;
	}

	if (LaunchClass == NULL)
	{
		LaunchClass = JNIHelper::env->FindClass("net/minecraft/launchwrapper/Launch");
		if (LaunchClass == NULL) return NULL;
	}
	
	if (ClassLoaderFieldID == NULL)
	{
		ClassLoaderFieldID = JNIHelper::env->GetStaticFieldID(LaunchClass, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
		if (ClassLoaderFieldID == NULL) return NULL;
	}

	if (ClassLoaderObject == NULL)
	{
		ClassLoaderObject = JNIHelper::env->GetStaticObjectField(LaunchClass, ClassLoaderFieldID);
		if (ClassLoaderObject == NULL) return NULL;
	}

	jstring jname = JNIHelper::env->NewStringUTF(name);
	jclass cls = (jclass)JNIHelper::env->CallObjectMethod(ClassLoaderObject, FindClassMethodID, jname);

	JNIHelper::env->DeleteLocalRef(jname);

	return cls;
}