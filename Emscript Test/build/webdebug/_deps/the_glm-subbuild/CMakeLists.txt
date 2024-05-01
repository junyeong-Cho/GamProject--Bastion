# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.22.1)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(the_glm-populate NONE)



include(ExternalProject)
ExternalProject_Add(the_glm-populate
                     "UPDATE_DISCONNECTED" "False" "DOWNLOAD_EXTRACT_TIMESTAMP" "TRUE" "URL" "https://github.com/g-truc/glm/releases/download/1.0.0/glm-1.0.0-light.7z"
                    SOURCE_DIR          "/mnt/c/Users/user/Desktop/임시폴더/GAM250/build/webdebug/_deps/the_glm-src/glm"
                    BINARY_DIR          "/mnt/c/Users/user/Desktop/임시폴더/GAM250/build/webdebug/_deps/the_glm-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


