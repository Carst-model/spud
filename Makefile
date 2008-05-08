#    Copyright (C) 2006 Imperial College London and others.
#
#    Please see the AUTHORS file in the main source directory for a full list
#    of copyright holders.
#
#    Prof. C Pain
#    Applied Modelling and Computation Group
#    Department of Earth Science and Engineering
#    Imperial College London
#
#    C.Pain@Imperial.ac.uk
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation,
#    version 2.1 of the License.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
#    USA

SHELL = /bin/sh

FC      = gfortran
FCFLAGS =  -DUSING_GFORTRAN=1 -DNDEBUG=1 -DDOUBLEP=1 -ffast-math -frecord-marker=4  -I/usr/include -ffree-line-length-none -ffixed-line-length-none  -O3 -fdefault-real-8 -Iinclude

CXX     = g++
CXXFLAGS=  -DUSING_GFORTRAN=1 -DNDEBUG=1 -DDOUBLEP=1 -g -O2 -Iinclude

MAKE    = make
AR  = ar
ARFLAGS = cr

LIB = libspud.a

VPATH = src/

OBJS = fspud.o spud.o tinystr.o tinyxmlerror.o tinyxml.o tinyxmlparser.o

.SUFFIXES: .f .f90 .F90 .F .c .cpp .o .a

.f90.o:
	$(FC) $(FCFLAGS) -c $<
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

default: $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)
clean:
	rm -f *.o

