#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = Scorch

# --------------------------------------------------------------
# Files to build

OBJS_DSP = \
	Scorch.cpp.o scorchcrafter.o
	
	OBJS_UI  = \
	DistrhoArtworkScorch.cpp.o \
	DistrhoUIScorch.cpp.o


# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
TARGETS += ladspa
# TARGETS += dssi
endif

TARGETS += lv2_dsp
TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
