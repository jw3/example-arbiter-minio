if (VERSION_PARSING_ERROR)
    message(FATAL_ERROR "git described version was not parsed correctly")
endif ()

set(CPACK_SET_DESTDIR ON)
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

include(dependencies)
include(CPack)
