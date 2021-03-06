# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.
add_library(app-glue STATIC
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library( # Sets the name of the library.
             first3d

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp
             src/main/cpp/NativeEngine.cpp
             src/main/cpp/Geometry.cpp
             src/main/cpp/Vector.cpp
             src/main/cpp/Scene.cpp
             src/main/cpp/Camera.cpp
             src/main/cpp/Transform.cpp
             src/main/cpp/ShaderLoader.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_include_directories(first3d PRIVATE

${ANDROID_NDK}/sources/android/native_app_glue
)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       first3d
                       android
                        app-glue
                        EGL
                        GLESv3
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
