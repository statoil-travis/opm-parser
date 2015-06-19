# -*- mode: cmake; tab-width: 2; indent-tabs-mode: t; truncate-lines: t; compile-command: "cmake -Wdev" -*-
# vim: set filetype=cmake autoindent tabstop=2 shiftwidth=2 noexpandtab softtabstop=2 nowrap:

# this avoids an annoying deprecation warning on DUNE 2.4 (which we
# are not interested in anyway)
set(DUNE_AVOID_CAPABILITIES_IS_PARALLEL_DEPRECATION_WARNING 1)

# defines that must be present in config.h for our headers
set (ewoms_CONFIG_VAR
	HAVE_QUAD
	HAVE_VALGRIND
	DUNE_AVOID_CAPABILITIES_IS_PARALLEL_DEPRECATION_WARNING
	)

# dependencies
set (ewoms_DEPS
	# compile with C++0x/11 support if available
	"CXX11Features REQUIRED"
	# DUNE prerequisites
	"dune-common REQUIRED"
	"dune-localfunctions REQUIRED"
	"dune-geometry REQUIRED"
	"dune-grid REQUIRED"
	"dune-istl REQUIRED"
	"opm-material REQUIRED"
	"dune-alugrid"
	"dune-cornerpoint"
	# librt (on some systems necessary for clock_gettime()) 
	"librt REQUIRED"
	# valgrind client requests
	"Valgrind"
	# quadruple precision floating point calculations
	"Quadmath"
	)