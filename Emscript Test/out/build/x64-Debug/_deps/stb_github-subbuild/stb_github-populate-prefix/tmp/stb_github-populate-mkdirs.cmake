# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-src"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-build"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix/tmp"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix/src/stb_github-populate-stamp"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix/src"
  "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix/src/stb_github-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix/src/stb_github-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/user/Documents/gam200-final-project-team_exodia/Emscript Test/out/build/x64-Debug/_deps/stb_github-subbuild/stb_github-populate-prefix/src/stb_github-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
