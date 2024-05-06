# from here:
#
# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

function(set_project_warnings project_name)
  option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" FALSE)

  # General MSVC warnings
  set(MSVC_WARNINGS
      /W3
      /permissive-
      /wd4201
      /wd4458  # suppress warning shadow
      /wd26439 # suppress warning non-virtual-dtor
      /wd4716  # suppress warning return-type
  )

  # General Clang and GCC shared warnings
  set(CLANG_GCC_SHARED_WARNINGS
      -Wall
      -Wextra
      -Wunused
      -Woverloaded-virtual
      -Wpedantic
      -Wconversion
      -Wnull-dereference
      -Wformat=2
      -Wno-gnu-anonymous-struct # allow anonymous-struct
      -Wno-nested-anon-types
      -Wno-unused-parameter # Suppress 'unused parameter'
      -Wno-nonportable-include-path
      -Wno-sign-conversion  # Suppress this specific warning
      -Wno-implicit-int-float-conversion
      -Wno-reorder-ctor
      -Wno-sign-compare
      -Wno-unused-variable
      -Wno-dev
  )

  # Clang specific warnings
  set(CLANG_WARNINGS
      ${CLANG_GCC_SHARED_WARNINGS}
      -Wno-shorten-64-to-32  # Suppress this specific warning
      -Wno-sign-conversion  # Suppress this specific warning
      -Wno-shadow
      -Wno-non-virtual-dtor
      -Wno-return-type
      -Wno-double-promotion
      -Wno-inconsistent-missing-override  
      -Wno-unused-private-field           
  )

  # GCC specific warnings
  set(GCC_WARNINGS
      ${CLANG_GCC_SHARED_WARNINGS}
      -Wmisleading-indentation
      -Wduplicated-cond
      -Wduplicated-branches
      -Wlogical-op
      -Wuseless-cast
      -Wno-shadow
      -Wno-non-virtual-dtor
      -Wno-return-type
  )

  if (WARNINGS_AS_ERRORS)
    list(APPEND CLANG_WARNINGS -Werror)
    list(APPEND GCC_WARNINGS -Werror)
    list(APPEND MSVC_WARNINGS /WX)
  endif()

  # Setting the appropriate warning flags based on the compiler
  if(MSVC)
    set(PROJECT_WARNINGS ${MSVC_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_WARNINGS ${CLANG_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_WARNINGS ${GCC_WARNINGS})
  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
endfunction()

