
set(GUI_CC_X11 x.cc)
set(GUI_CC_SDL sdl.cc)
set(GUI_CC_SDL2 sdl2.cc)
set(GUI_CC_WIN32 win32.cc)
set(GUI_CC_MACOS macintosh.cc)
set(GUI_CC_CARBON carbon.cc)
set(GUI_CC_NOGUI nogui.cc)
set(GUI_CC_TERM  term.cc)
set(GUI_CC_RFB rfb.cc)
set(GUI_CC_VNCSRV vncsrv.cc)
set(GUI_CC_AMIGAOS amigaos.cc)
set(GUI_CC_WX wx.cc)
set(GUI_CC_WX_SUPPORT wxmain.cc wxdialog.cc)

set(CI_CC_WIN32 win32config.cc)
set(CI_CC_WIN32_SUPPORT win32paramdlg.cc scrollwin.cc)

set(GUI_DLL_TARGETS  bx_sdl_gui.dll)
set(GUI_THAT_CANNOT_BE_PLUGINS keymap.cc gui.cc siminterface.cc paramtree.cc)

set(X_LIBS)
set(X_PRE_LIBS)
set(GUI_LINK_OPTS_X ${X_LIBS} ${X_PRE_LIBS})
set(GUI_LINK_OPTS_SDL -L/usr/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa)
set(GUI_LINK_OPTS_SDL2)
set(GUI_LINK_OPTS_RFB)
set(GUI_LINK_OPTS_RFB_VCPP user32.lib)
set(GUI_LINK_OPTS_VNCSRV)
set(GUI_LINK_OPTS_AMIGAOS)
set(GUI_LINK_OPTS_WIN32 -luser32 -lgdi32 -lcomctl32)
set(GUI_LINK_OPTS_WIN32_VCPP user32.lib gdi32.lib comctl32.lib)
set(GUI_LINK_OPTS_MACOS)
set(GUI_LINK_OPTS_CARBON -framework Carbon)
set(GUI_LINK_OPTS_NOGUI)
set(GUI_LINK_OPTS_TERM)
set(GUI_LINK_OPTS_WX)

set(CI_LINK_OPTS_WIN32 -luser32 -lgdi32 -lcomctl32 -lcomdlg32 -lshell32)
set(CI_LINK_OPTS_WIN32_VCPP user32.lib gdi32.lib comctl32.lib comdlg32.lib shell32.lib)

set(GUI_PLUGIN_CC ${GUI_CC_SDL})
set(GUI_CI_PLUGIN_CC textconfig.cc)
set(GUI_THAT_CAN_BE_PLUGINS ${GUI_PLUGIN_CC} ${GUI_CI_PLUGIN_CC})
set(GUI_THAT_SUPPORT_OTHER_PLUGINS)
set(GUI_NONPLUGIN_CC ${GUI_THAT_CANNOT_BE_PLUGINS} ${GUI_THAT_CAN_BE_PLUGINS} ${GUI_THAT_SUPPORT_OTHER_PLUGINS})


add_library(gui STATIC ${GUI_NONPLUGIN_CC})

target_include_directories(gui PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/..
${CMAKE_CURRENT_SOURCE_DIR}/../iodev
${CMAKE_CURRENT_SOURCE_DIR}/../instrument/stubs)

target_compile_options(gui PRIVATE -Wno-deprecated-declarations -Wno-braced-scalar-init)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL REQUIRED IMPORTED_TARGET sdl)

target_link_libraries(gui PRIVATE PkgConfig::SDL)