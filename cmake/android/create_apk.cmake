

set(ANDROID_APK_SIGNER_KEYSTORE	"~/my-release-key.keystore")
set(ANDROID_APK_SIGNER_ALIAS "myalias")

macro(create_apk name apk_package_name apk_directory libs_directory android_directory assets_directory ndk_api_level)

	set(ANDROID_NAME ${name})
	set(ANDROID_APK_PACKAGE ${apk_package_name})
	set(ANDROID_NATIVE_API_LEVEL ${ndk_api_level})

	add_custom_command(TARGET ${ANDROID_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E remove_directory "${apk_directory}/libs")
	add_custom_command(TARGET ${ANDROID_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E make_directory   "${apk_directory}/libs")
	add_custom_command(TARGET ${ANDROID_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory   "${CMAKE_SOURCE_DIR}/libs" "${apk_directory}/libs/")

	if(CMAKE_BUILD_TYPE MATCHES Release)
		set(ANDROID_APK_DEBUGGABLE "false")
	else()
		set(ANDROID_APK_DEBUGGABLE "true")
	endif()

	add_custom_command(TARGET ${ANDROID_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E make_directory   "${apk_directory}/res")
	add_custom_command(TARGET ${ANDROID_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E copy_directory   "${android_directory}/res" "${apk_directory}/res/")

	configure_file("${android_directory}/AndroidManifest.xml" "${apk_directory}/AndroidManifest.xml")

	add_custom_command(TARGET ${ANDROID_NAME} COMMAND android update project
		-t ${ANDROID_NATIVE_API_LEVEL}
		--name ${ANDROID_NAME}
		--path "${apk_directory}")

	add_custom_command(TARGET ${ANDROID_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E remove_directory "${apk_directory}/assets")
	add_custom_command(TARGET ${ANDROID_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E make_directory   "${apk_directory}/assets/")
	add_custom_command(TARGET ${ANDROID_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory   "${CMAKE_SOURCE_DIR}/assets" "${apk_directory}/assets/")

	if(CMAKE_BUILD_TYPE MATCHES Release)
		add_custom_command(TARGET ${ANDROID_NAME} COMMAND ant release WORKING_DIRECTORY "${apk_directory}")

		add_custom_command(TARGET ${ANDROID_NAME} COMMAND jarsigner -verbose
			-keystore ${ANDROID_APK_SIGNER_KEYSTORE}
			bin/${ANDROID_NAME}-unsigned.apk
			${ANDROID_APK_SIGNER_ALIAS}
			WORKING_DIRECTORY "${apk_directory}")

		add_custom_command(TARGET ${ANDROID_NAME} COMMAND zipalign -v -f 4
			bin/${ANDROID_NAME}-unsigned.apk
			bin/${ANDROID_NAME}.apk
			WORKING_DIRECTORY "${apk_directory}")
	else()
		add_custom_command(TARGET ${ANDROID_NAME} COMMAND ant debug WORKING_DIRECTORY "${apk_directory}")
	endif()

endmacro()
