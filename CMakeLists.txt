cmake_minimum_required(VERSION 3.8)
project(SHIELD)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/FindFontConfig.cmake)
include(cmake/FindWebP.cmake)

find_package(PythonLibs 2.7 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(WebP REQUIRED)
find_package(Boost COMPONENTS system python log REQUIRED)

set(SKIA_DIRECTORY "/home/malcolm/source/repos/skia")
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${SKIA_DIRECTORY}/include/core
        ${SKIA_DIRECTORY}/include/config
        ${SKIA_DIRECTORY}/include/effects
        ${SKIA_DIRECTORY}/include/ports
        ${SKIA_DIRECTORY}/include/utils
        ${SKIA_DIRECTORY}/include/svg
        ${SKIA_DIRECTORY}/include/pathops
        ${SKIA_DIRECTORY}/include/gpu
        ${SKIA_DIRECTORY}/include/privates
        ${SKIA_DIRECTORY}/src/gpu
        ${SKIA_DIRECTORY}/src/core
        ${SKIA_DIRECTORY}/src/views
        ${SKIA_DIRECTORY}/src/effects
        ${SKIA_DIRECTORY}/src/
        ${SKIA_DIRECTORY}/include/views
        )
set(SOURCE_FILES src/reed/PyBot.cpp src/reed/PyBot.h src/xavier/Messenger.cpp src/python/PyMessenger.cpp src/python/PyMessenger.h src/shield/Runner.cpp src/shield/Runner.h src/scarlet/App.cpp src/scarlet/App.h src/scarlet/GlContext.cpp src/scarlet/GlContext.h src/scarlet/NativeWindow.cpp src/scarlet/NativeWindow.h src/spidey/MatToBitmapConvertor.h src/scarlet/View.cpp src/scarlet/View.h src/shield/events/Event.cpp src/shield/events/Event.h src/scarlet/TextView.cpp src/scarlet/TextView.h src/shield/Captain.cpp src/shield/Captain.h src/scarlet/LinearLayout.cpp src/scarlet/LinearLayout.h src/scarlet/FixedView.cpp src/scarlet/FixedView.h src/scarlet/FlexView.cpp src/scarlet/FlexView.h src/shield/events/EventListener.h src/hawkeye/Camera.cpp src/hawkeye/Camera.h src/spidey/CircularQueue.cpp src/spidey/CircularQueue.h src/shield/CameraView.cpp src/shield/CameraView.h src/shield/events/TaskQueue.cpp src/shield/events/TaskQueue.h src/shield/SHIELD.cpp src/shield/SHIELD.h src/hawkeye/FrameCaptureEvent.cpp src/hawkeye/FrameCaptureEvent.h src/hawkeye/FrameCaptureEventListener.h src/shield/events/dispatcher.cpp src/shield/events/dispatcher.h src/hawkeye/HawkeyeView.cpp src/hawkeye/HawkeyeView.h src/shield/events/Processor.cpp src/shield/events/Processor.h src/hawkeye/FrameCaptureEventListener.cpp src/shield/IOService.cpp src/shield/IOService.h src/strange/Server.cpp src/strange/Server.h src/strange/TCPConnection.cpp src/strange/TCPConnection.h src/strange/ConnectionEvent.cpp src/strange/ConnectionEvent.h src/strange/ConnectionEventListener.cpp src/strange/ConnectionEventListener.h src/xavier/BotController.cpp src/xavier/BotController.h src/xavier/BotParameters.h src/reed/telemetics/Location.h src/reed/telemetics/Scalar.h src/reed/telemetics/Velocity.h src/shield/timer/Time.h src/reed/telemetics/Location.cpp src/reed/telemetics/BotTelematics.h src/reed/TelematicsCache.h src/reed/TelematicsMonitor.cpp src/reed/TelematicsMonitor.h src/reed/TelematicsEvent.cpp src/reed/TelematicsEvent.h src/shield/Bot.cpp src/shield/Bot.h src/reed/TelematicsView.cpp src/reed/TelematicsView.h src/reed/BotDetector.cpp src/reed/BotDetector.h src/reed/BotRegistry.cpp src/reed/BotRegistry.h src/reed/Reed.cpp src/reed/Reed.h src/xavier/Messenger.h src/reed/BotPollDetector.cpp src/reed/BotPollDetector.h)

set(EXE_SOURCE_FILES src/shield/main.cpp ${SOURCE_FILES})
add_executable(Avengers ${EXE_SOURCE_FILES} src/python/python_link.cpp)
set(LINK_LIBRARIES ${OpenCV_LIBS}
        ${SKIA_DIRECTORY}/out/Static/libskia.a
        ${GLUT_LIBRARIES}
        ${SDL2_LIBRARIES}
        Threads::Threads
        ${FREETYPE_LIBRARIES}
        ${CMAKE_DL_LIBS}
        ${FONTCONFIG_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${PNG_LIBRARIES}
        ${JPEG_LIBRARIES}
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
        libwebp.a)
target_link_libraries(Avengers ${LINK_LIBRARIES})

include_directories(${PYTHON_INCLUDE_PATH})
add_library(shield_cpp SHARED src/python/python_link.cpp ${SOURCE_FILES})
target_link_libraries(shield_cpp ${LINK_LIBRARIES})
set_target_properties(shield_cpp PROPERTIES PREFIX "")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/python/shield.py ${CMAKE_BINARY_DIR} COPYONLY)