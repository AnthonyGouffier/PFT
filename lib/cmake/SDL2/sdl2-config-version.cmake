# sdl2 cmake project-config-version input for ./configure scripts

<<<<<<< HEAD
set(PACKAGE_VERSION "2.26.2")
=======
set(PACKAGE_VERSION "2.26.4")
>>>>>>> origin/SDL

if(PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)
  set(PACKAGE_VERSION_COMPATIBLE FALSE)
else()
  set(PACKAGE_VERSION_COMPATIBLE TRUE)
  if(PACKAGE_FIND_VERSION STREQUAL PACKAGE_VERSION)
    set(PACKAGE_VERSION_EXACT TRUE)
  endif()
endif()
