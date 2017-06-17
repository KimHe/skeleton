##############################################################################
#
#    Makefile for GNU Make Utility to build the skeleton application.
#    Copyright (C) 2010 N. Yu. Zolotykh
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
##############################################################################



all: skeleton arageli install skeletonmex

.PHONY: check runexamples clean



DIR = $(shell pwd)

MATDIR = $(shell which matlab)
ifeq (, MATDIR)
	echo "MATLAB has not been installed, skeketon mex will not compiled"
endif

skeleton: arageli
	$(MAKE) -C src

arageli:
	$(MAKE) -C tools/arageli arageli

check: runexamples
	for name in $(notdir $(wildcard $(addsuffix /*.out, examples/golden.out))); do \
		if diff -q --strip-trailing-cr $(addsuffix /$$name, examples) $(addsuffix /$$name, examples/golden.out); \
			then echo $$name - passed; \
			else echo $$name - not passed; \
		fi; \
	done

runexamples: skeleton
	cd examples && $(SHELL) runexamples.sh

skeletonmex:
	matlab -nodesktop -nosplash -r "mex -I$(DIR)/src/ -I$(DIR)/tools/arageli/src $(DIR)/mex/skeletonmx.cpp $(DIR)/tools/arageli/lib/*.a; quit"
	mv skeletonmx.mex* mex/
	echo "The mex for skeleton has been successfully compiled,"
	echo " which is located in $(DIR)/mex"

install: 
	mv bin/skeleton /usr/local/bin/

clean:
	$(MAKE) -C tools/arageli clean
	$(MAKE) -C src clean
