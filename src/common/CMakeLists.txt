cmake_minimum_required (VERSION 2.6)
project (common)

set(SOURCES
		diagnostics/graph.cpp

		gl/gl_check.cpp

		base64.cpp
		env.cpp
		filesystem.cpp
		log.cpp
		tweener.cpp
		utf.cpp

		os/linux/filesystem.cpp
		os/linux/prec_timer.cpp
		os/linux/thread.cpp
)

set(HEADERS
		diagnostics/graph.h

		gl/gl_check.h

		os/filesystem.h
		os/thread.h

		array.h
		assert.h
		base64.h
		endian.h
		enum_class.h
		env.h
		executor.h
		except.h
		filesystem.h
		forward.h
		future.h
		log.h
		memory.h
		memshfl.h
		param.h
		prec_timer.h
		ptree.h
		scope_exit.h
		timer.h
		tweener.h
		utf.h
)

add_library(common ${SOURCES} ${HEADERS})

include_directories(..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${GLEW_INCLUDE_PATH})

source_group(sources ./*)
source_group(sources\\gl gl/*)
source_group(sources\\diagnostics diagnostics/*)
source_group(sources\\compiler\\vs compiler/vs/*)
source_group(sources\\os os/*)
