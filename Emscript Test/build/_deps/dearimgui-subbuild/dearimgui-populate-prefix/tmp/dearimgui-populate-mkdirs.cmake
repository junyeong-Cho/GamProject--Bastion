# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-src"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-build"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix/tmp"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix/src/dearimgui-populate-stamp"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix/src"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix/src/dearimgui-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix/src/dearimgui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/build/_deps/dearimgui-subbuild/dearimgui-populate-prefix/src/dearimgui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
