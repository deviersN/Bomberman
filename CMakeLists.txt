#-------------------------------------------------------------------------------
## PROJECT SETTINGS:

# Version of cmake required to build the project.
cmake_minimum_required(VERSION 3.0)

# Set type of version to build.
set(
	CMAKE_BUILD_TYPE
	"Debug"
)

# Project name and version.
project(Bomberman VERSION 0.1)

# Why always = Debug ??
message(">>	CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")


#-------------------------------------------------------------------------------
## WINDOWS SECTION:
if(WIN32)
	message(">>	WIN32 system detected")
	#-----------------------------------------------------------------------
	## LIBRARIES SETTINGS:

	# Print PROJECT_SOURCE_DIR to checks where it points.
	message(">>	PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

	# Find location of libraries.
	# find_library:
	# 	variable were to store result of find
	# 	names of the lib to find
	# 	paths were to search.
	find_library(
		IRRLICHT_LIB32
		NAMES Irrlicht.lib
		PATHS ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win32-visualstudio
	)
	message(">>	Found library IRRLICHT_LIB32 = ${IRRLICHT_LIB32}")
	find_library(
		IRRKLANG_LIB32
		NAMES irrKlang.lib
		PATHS ${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/lib/Win32-visualStudio
	)
	message(">>	Found library IRRKLANG_LIB32 = ${IRRKLANG_LIB32}")

	# Set libraries flags (like LDFLAGS).
	set(
		LIBRARIES_FLAGS
		opengl32 gdi32 winspool comdlg32 ole32 oleaut32 uuid odbc32 odbccp32
	)

	#-----------------------------------------------------------------------
	## EXECUTABLE SETTINGS:

	# Set compilation flags (like CFLAGS).
	# Use the flags found in the Makefile provided with Irrlicht example.
	set(
		CMAKE_CXX_FLAGS_RELEASE
		" -O3 -ffast-math -D_IRR_STATIC_LIB_ -std:c++14 -D_HAS_ITERATOR_DEBUGGING=0"
	)

	# Set directory where the executable will be placed.
	# If doesn't exists, the directory will be created.
	set(
		EXECUTABLE_OUTPUT_PATH
		${PROJECT_SOURCE_DIR}/exec_dir
	)

	# Directories to include (like -I).
	include_directories(
		${PROJECT_SOURCE_DIR}/inc
		${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/include
		${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/include
	)

	# Create the executable.
	add_executable(
		bomberman
		src/entity/ACharacter.cpp
		src/entity/Bomb.cpp
		src/entity/boost/ABoost.cpp
		src/entity/boost/BoostBombUp.cpp
		src/entity/boost/BoostFireUp.cpp
		src/entity/boost/BoostSpeedUp.cpp
		src/entity/boost/BoostWallPass.cpp
		src/entity/Flame.cpp
		src/entity/NPC.cpp
		src/entity/Player.cpp
		src/Exception.cpp
		src/game_map/Danger.cpp
		src/game_map/Map.cpp
		src/game_map/MapHandler.cpp
		src/Gui/EventReceiver.cpp
		src/Gui/Gui.cpp
		src/Main.cpp
		src/Parse/Loader.cpp
		src/Parse/Open.cpp
		src/Parse/Parse.cpp
		src/Sounds/Mixer.cpp
		src/Sounds/Sound.cpp
	)

	# Link the directories in where the libraries files are stored (.a, .so, ...)
	link_directories(
		${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win32-visualstudio
		${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/lib/Win32-visualStudio
	)

	# Link the libraries to the executable. The LDFLAGS part is call here too.
	target_link_libraries(
		bomberman
		${IRRLICHT_LIB32}
		${IRRKLANG_LIB32}
		${LIBRARIES_FLAGS}
	)
	message(">>	EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
	message(">>	EXECUTABLE_OUTPUT_PATH/CMAKE_BUILD_TYPE/ = ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/")
	# Copy required lib and plugins files to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/bin/Win32-VisualStudio/Irrlicht.dll
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/.
	)
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/bin/win32-visualStudio/irrKlang.dll
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/.
	)
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/bin/win32-visualStudio/ikpMP3.dll
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/
	)
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/bin/win32-visualStudio/ikpFlac.dll
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/
	)
	# Copy assets to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/assets
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/
	)
	# Copy configuration folder to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/conf
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/
	)
	# Copy game saves folder to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/save
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/
	)
	#-----------------------------------------------------------------------
	## INSTALLATION SETTINGS:

	# Install required files to specified directory.

	# RPATH ??
	# Wiki:
	# In computing, rpath designates the run-time search path hard-coded
	# in an executable file or library.
	# Dynamic linking loaders use the rpath to find required libraries.

	# Set rpath to the directory created by make install.
	set(
		CMAKE_INSTALL_RPATH
		$ENV{PROGRAMFILES}/INDIE_STUDIO
	)
	message(">>	CMAKE_INSTALL_RPATH = ${CMAKE_INSTALL_RPATH}")

	# Install the binary bomberman to the root of the installation directory.
	install(
		PROGRAMS ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/bomberman.exe
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir
	)
	# Install the libraries.
	install(
		DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir
		USE_SOURCE_PERMISSIONS
	)
	# Install the assets inside the exec_dir.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/assets/
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir/assets
		USE_SOURCE_PERMISSIONS
	)
	# Install the configuration folder inside the exec_dir.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/conf/
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir/conf
		USE_SOURCE_PERMISSIONS
	)
	# Install the saves folder inside the exec_dir.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/save/
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir/save
		USE_SOURCE_PERMISSIONS
	)
	# Install the plugins and lib for Irrklang.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/lib/irrKlang-1.6.0/bin/win32-visualStudio
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir
		USE_SOURCE_PERMISSIONS
	)
	# Install the lib for Irrlicht.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win32-visualStudio
		#DIRECTORY ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win32-gcc
		DESTINATION ${CMAKE_INSTALL_RPATH}/exec_dir
		USE_SOURCE_PERMISSIONS
	)

#-------------------------------------------------------------------------------
## UNIX SECTION:
else(WIN32) # UNIX SYSTEM
	message(">>	UNIX system detected")
	#-----------------------------------------------------------------------
	## LIBRARIES SETTINGS:

	# Print PROJECT_SOURCE_DIR to checks where it points.
	# message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

	# Find location of libraries.
	# find_library:
	# 	variable were to store result of find
	# 	names of the lib to find
	# 	paths were to search.
	find_library(
		IRRLICHT_LIB
		NAMES libIrrlicht.a
		PATHS ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux
	)
	message(">>	Found library IRRLICHT_LIB = ${IRRLICHT_LIB}")
	find_library(
		IRRKLANG_LIB
		NAMES libIrrKlang.so
		PATHS ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/bin/linux-gcc-64
	)
	message(">>	Found library IRRKLANG_LIB = ${IRRKLANG_LIB}")

	# Set libraries flags (like LDFLAGS).
	set(
		LIBRARIES_FLAGS
		GL Xxf86vm Xext X11 Xcursor pthread
	)

	#-----------------------------------------------------------------------
	## EXECUTABLE SETTINGS:

	# Set compilation flags (like CFLAGS).
	# Use the flags found in the Makefile provided with Irrlicht example.
	set(
		CMAKE_CXX_FLAGS_RELEASE
		" -O3 -ffast-math -std=c++11"
	)

	# Set directory where the executable will be placed.
	# If doesn't exists, the directory will be created.
	set(
		EXECUTABLE_OUTPUT_PATH
		${PROJECT_SOURCE_DIR}/exec_dir/${CMAKE_BUILD_TYPE}
	)

	# Directories to include (like -I).
	include_directories(
		${PROJECT_SOURCE_DIR}/inc
		${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/include
		${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/include
	)

	# Create the executable.
	add_executable(
		bomberman
		src/entity/ACharacter.cpp
		src/entity/Bomb.cpp
		src/entity/boost/ABoost.cpp
		src/entity/boost/BoostBombUp.cpp
		src/entity/boost/BoostFireUp.cpp
		src/entity/boost/BoostSpeedUp.cpp
		src/entity/boost/BoostWallPass.cpp
		src/entity/Flame.cpp
		src/entity/NPC.cpp
		src/entity/Player.cpp
		src/Exception.cpp
		src/game_map/Danger.cpp
		src/game_map/Map.cpp
		src/game_map/MapHandler.cpp
		src/Gui/EventReceiver.cpp
		src/Gui/Gui.cpp
		src/Main.cpp
		src/Parse/Loader.cpp
		src/Parse/Open.cpp
		src/Parse/Parse.cpp
		src/Sounds/Mixer.cpp
		src/Sounds/Sound.cpp
	)

	# Link the directories in where the libraries files are stored (.a, .so, ...)
	link_directories(
		${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux
		${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/bin/linux-gcc-64
	)

	# Link the libraries to the executable. The LDFLAGS part is call here too.
	target_link_libraries(
		bomberman
		${IRRLICHT_LIB}
		${IRRKLANG_LIB}
		${LIBRARIES_FLAGS}
	)

	message(">>	EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
	# Copy required lib and plugins files to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/bin/linux-gcc-64/libIrrKlang.so
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}
	)
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/bin/linux-gcc-64/ikpMP3.so
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}
	)
	file(
		COPY ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/bin/linux-gcc-64/ikpFlac.so
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}
	)
	# Copy assets to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/assets
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}
	)
	# Copy configuration folder to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/conf
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}
	)
	# Copy game saves folder to the executable destination.
	file(
		COPY ${PROJECT_SOURCE_DIR}/save
		DESTINATION ${EXECUTABLE_OUTPUT_PATH}
	)
	#-----------------------------------------------------------------------
	## INSTALLATION SETTINGS:

	# Install required files to specified directory.

	# RPATH ??
	# Wiki:
	# In computing, rpath designates the run-time search path hard-coded
	# in an executable file or library.
	# Dynamic linking loaders use the rpath to find required libraries.

	# Set rpath to the directory created by make install.
	set(
		CMAKE_INSTALL_RPATH
		$ENV{HOME}/INDIE_STUDIO
	)
	message(">>	CMAKE_INSTALL_RPATH = ${CMAKE_INSTALL_RPATH}")

	# Install the binary bomberman.
	install(
		PROGRAMS ${EXECUTABLE_OUTPUT_PATH}/bomberman
		DESTINATION ${CMAKE_INSTALL_RPATH}/bin
	)
	# Install the assets inside the exec_dir.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/assets/
		DESTINATION ${CMAKE_INSTALL_RPATH}/bin/assets
		USE_SOURCE_PERMISSIONS
	)
	# Install the configuration folder inside the exec_dir.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/conf/
		DESTINATION ${CMAKE_INSTALL_RPATH}/bin/conf
		USE_SOURCE_PERMISSIONS
	)
	# Install the saves folder inside the exec_dir.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/save/
		DESTINATION ${CMAKE_INSTALL_RPATH}/bin/save
		USE_SOURCE_PERMISSIONS
	)
	# Install the plugins and lib for Irrklang.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/lib/irrKlang-64bit-1.6.0/bin/linux-gcc-64
		DESTINATION ${CMAKE_INSTALL_RPATH}/bin
		USE_SOURCE_PERMISSIONS
	)
	# Install the lib for Irrlicht.
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Linux
		DESTINATION ${CMAKE_INSTALL_RPATH}/bin
		USE_SOURCE_PERMISSIONS
	)

endif(WIN32)
