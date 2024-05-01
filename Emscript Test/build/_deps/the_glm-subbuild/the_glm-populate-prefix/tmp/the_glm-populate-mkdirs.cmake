# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-src/glm"
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-build"
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix"
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix/tmp"
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix/src/the_glm-populate-stamp"
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix/src"
  "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix/src/the_glm-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix/src/the_glm-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/user/Desktop/임시폴더/GAM250/build/_deps/the_glm-subbuild/the_glm-populate-prefix/src/the_glm-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
