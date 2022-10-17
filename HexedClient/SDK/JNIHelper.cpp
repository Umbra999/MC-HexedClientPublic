#include "JNIHelper.hpp"

jclass JNIHelper::ForgeFindClass(const char* name)
{
	if (classloader_obj == NULL || findclass_md == NULL)
	{
		jclass launchwrapper_cls = JNIHelper::env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");

		jclass launch_cls = JNIHelper::env->FindClass("net/minecraft/launchwrapper/Launch");

		auto classloader_fid = JNIHelper::env->GetStaticFieldID(launch_cls, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");

		findclass_md = JNIHelper::env->GetMethodID(launchwrapper_cls, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		classloader_obj = JNIHelper::env->NewGlobalRef(JNIHelper::env->GetStaticObjectField(launch_cls, classloader_fid));

		JNIHelper::env->DeleteLocalRef(launchwrapper_cls);
		JNIHelper::env->DeleteLocalRef(launch_cls);
	}

	jstring jname = JNIHelper::env->NewStringUTF(name);
	jclass cls = reinterpret_cast<jclass>(JNIHelper::env->CallObjectMethod(classloader_obj, findclass_md, jname));

	JNIHelper::env->DeleteLocalRef(jname);

	return cls;
}