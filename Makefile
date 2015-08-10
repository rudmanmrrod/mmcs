#############################################################################
# Makefile for building: SMSAM
# Generated by qmake (2.01a) (Qt 4.8.2) on: Thu Aug 6 15:07:36 2015
# Project:  SMSAM.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile SMSAM.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -Iarmadillo_bits -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L -larmadillo -llapack -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = mainwindow.C \
		main.C \
		formloadmatrix.C \
		formviewmatrix.C \
		stackwidget.C \
		accountwidget.C \
		formvariablesexogenas.cpp \
		stackvariablesexogenas.cpp \
		variableexogenawidget.cpp \
		formexportmatrix.cpp moc_mainwindow.cpp \
		moc_formloadmatrix.cpp \
		moc_formviewmatrix.cpp \
		moc_stackwidget.cpp \
		moc_accountwidget.cpp \
		moc_formvariablesexogenas.cpp \
		moc_stackvariablesexogenas.cpp \
		moc_variableexogenawidget.cpp \
		moc_formexportmatrix.cpp
OBJECTS       = mainwindow.o \
		main.o \
		formloadmatrix.o \
		formviewmatrix.o \
		stackwidget.o \
		accountwidget.o \
		formvariablesexogenas.o \
		stackvariablesexogenas.o \
		variableexogenawidget.o \
		formexportmatrix.o \
		moc_mainwindow.o \
		moc_formloadmatrix.o \
		moc_formviewmatrix.o \
		moc_stackwidget.o \
		moc_accountwidget.o \
		moc_formvariablesexogenas.o \
		moc_stackvariablesexogenas.o \
		moc_variableexogenawidget.o \
		moc_formexportmatrix.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		SMSAM.pro
QMAKE_TARGET  = SMSAM
DESTDIR       = 
TARGET        = SMSAM

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_formLoadMatrix.h ui_formMatrixView.h ui_formvariablesexogenas.h ui_formexportmatrix.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: SMSAM.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile SMSAM.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile SMSAM.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/SMSAM1.0.0 || $(MKDIR) .tmp/SMSAM1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents mainwindow.H formloadmatrix.H formviewmatrix.H stackwidget.H accountwidget.H formvariablesexogenas.h stackvariablesexogenas.h variableexogenawidget.h formexportmatrix.h .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents mainwindow.C main.C formloadmatrix.C formviewmatrix.C stackwidget.C accountwidget.C formvariablesexogenas.cpp stackvariablesexogenas.cpp variableexogenawidget.cpp formexportmatrix.cpp .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents formLoadMatrix.ui formMatrixView.ui formvariablesexogenas.ui formexportmatrix.ui .tmp/SMSAM1.0.0/ && (cd `dirname .tmp/SMSAM1.0.0` && $(TAR) SMSAM1.0.0.tar SMSAM1.0.0 && $(COMPRESS) SMSAM1.0.0.tar) && $(MOVE) `dirname .tmp/SMSAM1.0.0`/SMSAM1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/SMSAM1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_formloadmatrix.cpp moc_formviewmatrix.cpp moc_stackwidget.cpp moc_accountwidget.cpp moc_formvariablesexogenas.cpp moc_stackvariablesexogenas.cpp moc_variableexogenawidget.cpp moc_formexportmatrix.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_formloadmatrix.cpp moc_formviewmatrix.cpp moc_stackwidget.cpp moc_accountwidget.cpp moc_formvariablesexogenas.cpp moc_stackvariablesexogenas.cpp moc_variableexogenawidget.cpp moc_formexportmatrix.cpp
moc_mainwindow.cpp: formloadmatrix.H \
		ui_formLoadMatrix.h \
		formviewmatrix.H \
		ui_formMatrixView.h \
		formvariablesexogenas.h \
		stackwidget.H \
		accountwidget.H \
		stackvariablesexogenas.h \
		variableexogenawidget.h \
		formexportmatrix.h \
		mainwindow.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.H -o moc_mainwindow.cpp

moc_formloadmatrix.cpp: ui_formLoadMatrix.h \
		formloadmatrix.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formloadmatrix.H -o moc_formloadmatrix.cpp

moc_formviewmatrix.cpp: ui_formMatrixView.h \
		formviewmatrix.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formviewmatrix.H -o moc_formviewmatrix.cpp

moc_stackwidget.cpp: accountwidget.H \
		stackwidget.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) stackwidget.H -o moc_stackwidget.cpp

moc_accountwidget.cpp: accountwidget.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) accountwidget.H -o moc_accountwidget.cpp

moc_formvariablesexogenas.cpp: formvariablesexogenas.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formvariablesexogenas.h -o moc_formvariablesexogenas.cpp

moc_stackvariablesexogenas.cpp: variableexogenawidget.h \
		stackvariablesexogenas.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) stackvariablesexogenas.h -o moc_stackvariablesexogenas.cpp

moc_variableexogenawidget.cpp: variableexogenawidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) variableexogenawidget.h -o moc_variableexogenawidget.cpp

moc_formexportmatrix.cpp: formexportmatrix.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formexportmatrix.h -o moc_formexportmatrix.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_formLoadMatrix.h ui_formMatrixView.h ui_formvariablesexogenas.h ui_formexportmatrix.h
compiler_uic_clean:
	-$(DEL_FILE) ui_formLoadMatrix.h ui_formMatrixView.h ui_formvariablesexogenas.h ui_formexportmatrix.h
ui_formLoadMatrix.h: formLoadMatrix.ui
	/usr/bin/uic-qt4 formLoadMatrix.ui -o ui_formLoadMatrix.h

ui_formMatrixView.h: formMatrixView.ui
	/usr/bin/uic-qt4 formMatrixView.ui -o ui_formMatrixView.h

ui_formvariablesexogenas.h: formvariablesexogenas.ui
	/usr/bin/uic-qt4 formvariablesexogenas.ui -o ui_formvariablesexogenas.h

ui_formexportmatrix.h: formexportmatrix.ui
	/usr/bin/uic-qt4 formexportmatrix.ui -o ui_formexportmatrix.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

mainwindow.o: mainwindow.C mainwindow.H \
		formloadmatrix.H \
		ui_formLoadMatrix.h \
		formviewmatrix.H \
		ui_formMatrixView.h \
		formvariablesexogenas.h \
		stackwidget.H \
		accountwidget.H \
		stackvariablesexogenas.h \
		variableexogenawidget.h \
		formexportmatrix.h \
		armadillo \
		armadillo_bits/config.hpp \
		armadillo_bits/compiler_setup.hpp \
		armadillo_bits/include_atlas.hpp \
		armadillo_bits/include_hdf5.hpp \
		armadillo_bits/include_superlu.hpp \
		armadillo_bits/forward_bones.hpp \
		armadillo_bits/arma_static_check.hpp \
		armadillo_bits/typedef_elem.hpp \
		armadillo_bits/typedef_elem_check.hpp \
		armadillo_bits/typedef_mat.hpp \
		armadillo_bits/arma_boost.hpp \
		armadillo_bits/arma_version.hpp \
		armadillo_bits/arma_config.hpp \
		armadillo_bits/traits.hpp \
		armadillo_bits/promote_type.hpp \
		armadillo_bits/upgrade_val.hpp \
		armadillo_bits/restrictors.hpp \
		armadillo_bits/access.hpp \
		armadillo_bits/span.hpp \
		armadillo_bits/distr_param.hpp \
		armadillo_bits/constants.hpp \
		armadillo_bits/constants_compat.hpp \
		armadillo_bits/arma_rng_cxx98.hpp \
		armadillo_bits/arma_rng_cxx11.hpp \
		armadillo_bits/arma_rng.hpp \
		armadillo_bits/Base_bones.hpp \
		armadillo_bits/BaseCube_bones.hpp \
		armadillo_bits/SpBase_bones.hpp \
		armadillo_bits/blas_bones.hpp \
		armadillo_bits/lapack_bones.hpp \
		armadillo_bits/atlas_bones.hpp \
		armadillo_bits/arpack_bones.hpp \
		armadillo_bits/superlu_bones.hpp \
		armadillo_bits/hdf5_bones.hpp \
		armadillo_bits/blas_wrapper.hpp \
		armadillo_bits/lapack_wrapper.hpp \
		armadillo_bits/atlas_wrapper.hpp \
		armadillo_bits/arpack_wrapper.hpp \
		armadillo_bits/superlu_wrapper.hpp \
		armadillo_bits/cond_rel_bones.hpp \
		armadillo_bits/arrayops_bones.hpp \
		armadillo_bits/podarray_bones.hpp \
		armadillo_bits/auxlib_bones.hpp \
		armadillo_bits/sp_auxlib_bones.hpp \
		armadillo_bits/injector_bones.hpp \
		armadillo_bits/Mat_bones.hpp \
		armadillo_bits/Col_bones.hpp \
		armadillo_bits/Row_bones.hpp \
		armadillo_bits/Cube_bones.hpp \
		armadillo_bits/xvec_htrans_bones.hpp \
		armadillo_bits/xtrans_mat_bones.hpp \
		armadillo_bits/SizeMat_bones.hpp \
		armadillo_bits/SizeCube_bones.hpp \
		armadillo_bits/SpValProxy_bones.hpp \
		armadillo_bits/SpMat_bones.hpp \
		armadillo_bits/SpCol_bones.hpp \
		armadillo_bits/SpRow_bones.hpp \
		armadillo_bits/SpSubview_bones.hpp \
		armadillo_bits/spdiagview_bones.hpp \
		armadillo_bits/typedef_mat_fixed.hpp \
		armadillo_bits/field_bones.hpp \
		armadillo_bits/subview_bones.hpp \
		armadillo_bits/subview_elem1_bones.hpp \
		armadillo_bits/subview_elem2_bones.hpp \
		armadillo_bits/subview_field_bones.hpp \
		armadillo_bits/subview_cube_bones.hpp \
		armadillo_bits/diagview_bones.hpp \
		armadillo_bits/subview_each_bones.hpp \
		armadillo_bits/diskio_bones.hpp \
		armadillo_bits/wall_clock_bones.hpp \
		armadillo_bits/running_stat_bones.hpp \
		armadillo_bits/running_stat_vec_bones.hpp \
		armadillo_bits/Op_bones.hpp \
		armadillo_bits/OpCube_bones.hpp \
		armadillo_bits/SpOp_bones.hpp \
		armadillo_bits/eOp_bones.hpp \
		armadillo_bits/eOpCube_bones.hpp \
		armadillo_bits/mtOp_bones.hpp \
		armadillo_bits/mtOpCube_bones.hpp \
		armadillo_bits/mtSpOp_bones.hpp \
		armadillo_bits/Glue_bones.hpp \
		armadillo_bits/eGlue_bones.hpp \
		armadillo_bits/mtGlue_bones.hpp \
		armadillo_bits/SpGlue_bones.hpp \
		armadillo_bits/GlueCube_bones.hpp \
		armadillo_bits/eGlueCube_bones.hpp \
		armadillo_bits/mtGlueCube_bones.hpp \
		armadillo_bits/eop_core_bones.hpp \
		armadillo_bits/eglue_core_bones.hpp \
		armadillo_bits/Gen_bones.hpp \
		armadillo_bits/GenCube_bones.hpp \
		armadillo_bits/op_diagmat_bones.hpp \
		armadillo_bits/op_diagvec_bones.hpp \
		armadillo_bits/op_dot_bones.hpp \
		armadillo_bits/op_inv_bones.hpp \
		armadillo_bits/op_htrans_bones.hpp \
		armadillo_bits/op_max_bones.hpp \
		armadillo_bits/op_min_bones.hpp \
		armadillo_bits/op_mean_bones.hpp \
		armadillo_bits/op_median_bones.hpp \
		armadillo_bits/op_sort_bones.hpp \
		armadillo_bits/op_sort_index_bones.hpp \
		armadillo_bits/op_sum_bones.hpp \
		armadillo_bits/op_stddev_bones.hpp \
		armadillo_bits/op_strans_bones.hpp \
		armadillo_bits/op_var_bones.hpp \
		armadillo_bits/op_repmat_bones.hpp \
		armadillo_bits/op_reshape_bones.hpp \
		armadillo_bits/op_vectorise_bones.hpp \
		armadillo_bits/op_resize_bones.hpp \
		armadillo_bits/op_cov_bones.hpp \
		armadillo_bits/op_cor_bones.hpp \
		armadillo_bits/op_shuffle_bones.hpp \
		armadillo_bits/op_prod_bones.hpp \
		armadillo_bits/op_pinv_bones.hpp \
		armadillo_bits/op_dotext_bones.hpp \
		armadillo_bits/op_flip_bones.hpp \
		armadillo_bits/op_princomp_bones.hpp \
		armadillo_bits/op_misc_bones.hpp \
		armadillo_bits/op_relational_bones.hpp \
		armadillo_bits/op_find_bones.hpp \
		armadillo_bits/op_chol_bones.hpp \
		armadillo_bits/op_cx_scalar_bones.hpp \
		armadillo_bits/op_trimat_bones.hpp \
		armadillo_bits/op_cumsum_bones.hpp \
		armadillo_bits/op_symmat_bones.hpp \
		armadillo_bits/op_hist_bones.hpp \
		armadillo_bits/op_unique_bones.hpp \
		armadillo_bits/op_toeplitz_bones.hpp \
		armadillo_bits/op_fft_bones.hpp \
		armadillo_bits/op_any_bones.hpp \
		armadillo_bits/op_all_bones.hpp \
		armadillo_bits/op_normalise_bones.hpp \
		armadillo_bits/op_clamp_bones.hpp \
		armadillo_bits/op_expmat_bones.hpp \
		armadillo_bits/op_nonzeros_bones.hpp \
		armadillo_bits/glue_times_bones.hpp \
		armadillo_bits/glue_mixed_bones.hpp \
		armadillo_bits/glue_cov_bones.hpp \
		armadillo_bits/glue_cor_bones.hpp \
		armadillo_bits/glue_kron_bones.hpp \
		armadillo_bits/glue_cross_bones.hpp \
		armadillo_bits/glue_join_bones.hpp \
		armadillo_bits/glue_relational_bones.hpp \
		armadillo_bits/glue_solve_bones.hpp \
		armadillo_bits/glue_conv_bones.hpp \
		armadillo_bits/glue_toeplitz_bones.hpp \
		armadillo_bits/glue_hist_bones.hpp \
		armadillo_bits/glue_histc_bones.hpp \
		armadillo_bits/glue_max_bones.hpp \
		armadillo_bits/glue_min_bones.hpp \
		armadillo_bits/spop_max_bones.hpp \
		armadillo_bits/spop_min_bones.hpp \
		armadillo_bits/spop_sum_bones.hpp \
		armadillo_bits/spop_strans_bones.hpp \
		armadillo_bits/spop_htrans_bones.hpp \
		armadillo_bits/spop_misc_bones.hpp \
		armadillo_bits/spop_mean_bones.hpp \
		armadillo_bits/spop_var_bones.hpp \
		armadillo_bits/spglue_plus_bones.hpp \
		armadillo_bits/spglue_minus_bones.hpp \
		armadillo_bits/spglue_times_bones.hpp \
		armadillo_bits/spglue_join_bones.hpp \
		armadillo_bits/debug.hpp \
		armadillo_bits/memory.hpp \
		armadillo_bits/arma_cmath.hpp \
		armadillo_bits/unwrap.hpp \
		armadillo_bits/unwrap_cube.hpp \
		armadillo_bits/unwrap_spmat.hpp \
		armadillo_bits/Proxy.hpp \
		armadillo_bits/ProxyCube.hpp \
		armadillo_bits/SpProxy.hpp \
		armadillo_bits/diagmat_proxy.hpp \
		armadillo_bits/strip.hpp \
		armadillo_bits/Op_meat.hpp \
		armadillo_bits/OpCube_meat.hpp \
		armadillo_bits/SpOp_meat.hpp \
		armadillo_bits/mtOp_meat.hpp \
		armadillo_bits/mtOpCube_meat.hpp \
		armadillo_bits/mtSpOp_meat.hpp \
		armadillo_bits/Glue_meat.hpp \
		armadillo_bits/GlueCube_meat.hpp \
		armadillo_bits/SpGlue_meat.hpp \
		armadillo_bits/eop_aux.hpp \
		armadillo_bits/eOp_meat.hpp \
		armadillo_bits/eOpCube_meat.hpp \
		armadillo_bits/eGlue_meat.hpp \
		armadillo_bits/eGlueCube_meat.hpp \
		armadillo_bits/mtGlue_meat.hpp \
		armadillo_bits/mtGlueCube_meat.hpp \
		armadillo_bits/Base_meat.hpp \
		armadillo_bits/BaseCube_meat.hpp \
		armadillo_bits/SpBase_meat.hpp \
		armadillo_bits/Gen_meat.hpp \
		armadillo_bits/GenCube_meat.hpp \
		armadillo_bits/arma_ostream_bones.hpp \
		armadillo_bits/arma_ostream_meat.hpp \
		armadillo_bits/fn_n_unique.hpp \
		armadillo_bits/operator_plus.hpp \
		armadillo_bits/operator_minus.hpp \
		armadillo_bits/operator_times.hpp \
		armadillo_bits/operator_schur.hpp \
		armadillo_bits/operator_div.hpp \
		armadillo_bits/operator_relational.hpp \
		armadillo_bits/operator_cube_plus.hpp \
		armadillo_bits/operator_cube_minus.hpp \
		armadillo_bits/operator_cube_times.hpp \
		armadillo_bits/operator_cube_schur.hpp \
		armadillo_bits/operator_cube_div.hpp \
		armadillo_bits/operator_cube_relational.hpp \
		armadillo_bits/operator_ostream.hpp \
		armadillo_bits/fn_conv_to.hpp \
		armadillo_bits/fn_min.hpp \
		armadillo_bits/fn_max.hpp \
		armadillo_bits/fn_accu.hpp \
		armadillo_bits/fn_sum.hpp \
		armadillo_bits/fn_diagmat.hpp \
		armadillo_bits/fn_diagvec.hpp \
		armadillo_bits/fn_inv.hpp \
		armadillo_bits/fn_trace.hpp \
		armadillo_bits/fn_trans.hpp \
		armadillo_bits/fn_det.hpp \
		armadillo_bits/fn_log_det.hpp \
		armadillo_bits/fn_eig_sym.hpp \
		armadillo_bits/fn_eig_gen.hpp \
		armadillo_bits/fn_eig_pair.hpp \
		armadillo_bits/fn_lu.hpp \
		armadillo_bits/fn_zeros.hpp \
		armadillo_bits/fn_ones.hpp \
		armadillo_bits/fn_eye.hpp \
		armadillo_bits/fn_misc.hpp \
		armadillo_bits/fn_find.hpp \
		armadillo_bits/fn_elem.hpp \
		armadillo_bits/fn_norm.hpp \
		armadillo_bits/fn_dot.hpp \
		armadillo_bits/fn_randu.hpp \
		armadillo_bits/fn_randn.hpp \
		armadillo_bits/fn_trig.hpp \
		armadillo_bits/fn_mean.hpp \
		armadillo_bits/fn_median.hpp \
		armadillo_bits/fn_stddev.hpp \
		armadillo_bits/fn_var.hpp \
		armadillo_bits/fn_sort.hpp \
		armadillo_bits/fn_sort_index.hpp \
		armadillo_bits/fn_strans.hpp \
		armadillo_bits/fn_chol.hpp \
		armadillo_bits/fn_qr.hpp \
		armadillo_bits/fn_svd.hpp \
		armadillo_bits/fn_solve.hpp \
		armadillo_bits/fn_repmat.hpp \
		armadillo_bits/fn_reshape.hpp \
		armadillo_bits/fn_vectorise.hpp \
		armadillo_bits/fn_resize.hpp \
		armadillo_bits/fn_cov.hpp \
		armadillo_bits/fn_cor.hpp \
		armadillo_bits/fn_shuffle.hpp \
		armadillo_bits/fn_prod.hpp \
		armadillo_bits/fn_eps.hpp \
		armadillo_bits/fn_pinv.hpp \
		armadillo_bits/fn_rank.hpp \
		armadillo_bits/fn_kron.hpp \
		armadillo_bits/fn_flip.hpp \
		armadillo_bits/fn_as_scalar.hpp \
		armadillo_bits/fn_princomp.hpp \
		armadillo_bits/fn_cross.hpp \
		armadillo_bits/fn_join.hpp \
		armadillo_bits/fn_conv.hpp \
		armadillo_bits/fn_trunc_exp.hpp \
		armadillo_bits/fn_trunc_log.hpp \
		armadillo_bits/fn_toeplitz.hpp \
		armadillo_bits/fn_trimat.hpp \
		armadillo_bits/fn_cumsum.hpp \
		armadillo_bits/fn_symmat.hpp \
		armadillo_bits/fn_syl_lyap.hpp \
		armadillo_bits/fn_hist.hpp \
		armadillo_bits/fn_histc.hpp \
		armadillo_bits/fn_unique.hpp \
		armadillo_bits/fn_fft.hpp \
		armadillo_bits/fn_fft2.hpp \
		armadillo_bits/fn_any.hpp \
		armadillo_bits/fn_all.hpp \
		armadillo_bits/fn_size.hpp \
		armadillo_bits/fn_numel.hpp \
		armadillo_bits/fn_inplace_strans.hpp \
		armadillo_bits/fn_inplace_trans.hpp \
		armadillo_bits/fn_randi.hpp \
		armadillo_bits/fn_randg.hpp \
		armadillo_bits/fn_cond.hpp \
		armadillo_bits/fn_normalise.hpp \
		armadillo_bits/fn_clamp.hpp \
		armadillo_bits/fn_expmat.hpp \
		armadillo_bits/fn_nonzeros.hpp \
		armadillo_bits/fn_interp1.hpp \
		armadillo_bits/fn_speye.hpp \
		armadillo_bits/fn_spones.hpp \
		armadillo_bits/fn_sprandn.hpp \
		armadillo_bits/fn_sprandu.hpp \
		armadillo_bits/fn_eigs_sym.hpp \
		armadillo_bits/fn_eigs_gen.hpp \
		armadillo_bits/fn_norm_sparse.hpp \
		armadillo_bits/fn_spsolve.hpp \
		armadillo_bits/fn_svds.hpp \
		armadillo_bits/hdf5_misc.hpp \
		armadillo_bits/fft_engine.hpp \
		armadillo_bits/gmm_misc_bones.hpp \
		armadillo_bits/gmm_misc_meat.hpp \
		armadillo_bits/gmm_diag_bones.hpp \
		armadillo_bits/gmm_diag_meat.hpp \
		armadillo_bits/mul_gemv.hpp \
		armadillo_bits/mul_gemm.hpp \
		armadillo_bits/mul_gemm_mixed.hpp \
		armadillo_bits/mul_syrk.hpp \
		armadillo_bits/mul_herk.hpp \
		armadillo_bits/eop_core_meat.hpp \
		armadillo_bits/eglue_core_meat.hpp \
		armadillo_bits/cond_rel_meat.hpp \
		armadillo_bits/arrayops_meat.hpp \
		armadillo_bits/podarray_meat.hpp \
		armadillo_bits/auxlib_meat.hpp \
		armadillo_bits/sp_auxlib_meat.hpp \
		armadillo_bits/injector_meat.hpp \
		armadillo_bits/Mat_meat.hpp \
		armadillo_bits/Col_meat.hpp \
		armadillo_bits/Row_meat.hpp \
		armadillo_bits/Cube_meat.hpp \
		armadillo_bits/xvec_htrans_meat.hpp \
		armadillo_bits/xtrans_mat_meat.hpp \
		armadillo_bits/SizeMat_meat.hpp \
		armadillo_bits/SizeCube_meat.hpp \
		armadillo_bits/field_meat.hpp \
		armadillo_bits/subview_meat.hpp \
		armadillo_bits/subview_elem1_meat.hpp \
		armadillo_bits/subview_elem2_meat.hpp \
		armadillo_bits/subview_field_meat.hpp \
		armadillo_bits/subview_cube_meat.hpp \
		armadillo_bits/diagview_meat.hpp \
		armadillo_bits/subview_each_meat.hpp \
		armadillo_bits/SpValProxy_meat.hpp \
		armadillo_bits/SpMat_meat.hpp \
		armadillo_bits/SpMat_iterators_meat.hpp \
		armadillo_bits/SpCol_meat.hpp \
		armadillo_bits/SpRow_meat.hpp \
		armadillo_bits/SpSubview_meat.hpp \
		armadillo_bits/SpSubview_iterators_meat.hpp \
		armadillo_bits/spdiagview_meat.hpp \
		armadillo_bits/diskio_meat.hpp \
		armadillo_bits/wall_clock_meat.hpp \
		armadillo_bits/running_stat_meat.hpp \
		armadillo_bits/running_stat_vec_meat.hpp \
		armadillo_bits/op_diagmat_meat.hpp \
		armadillo_bits/op_diagvec_meat.hpp \
		armadillo_bits/op_dot_meat.hpp \
		armadillo_bits/op_inv_meat.hpp \
		armadillo_bits/op_htrans_meat.hpp \
		armadillo_bits/op_max_meat.hpp \
		armadillo_bits/op_min_meat.hpp \
		armadillo_bits/op_mean_meat.hpp \
		armadillo_bits/op_median_meat.hpp \
		armadillo_bits/op_sort_meat.hpp \
		armadillo_bits/op_sort_index_meat.hpp \
		armadillo_bits/op_sum_meat.hpp \
		armadillo_bits/op_stddev_meat.hpp \
		armadillo_bits/op_strans_meat.hpp \
		armadillo_bits/op_var_meat.hpp \
		armadillo_bits/op_repmat_meat.hpp \
		armadillo_bits/op_reshape_meat.hpp \
		armadillo_bits/op_vectorise_meat.hpp \
		armadillo_bits/op_resize_meat.hpp \
		armadillo_bits/op_cov_meat.hpp \
		armadillo_bits/op_cor_meat.hpp \
		armadillo_bits/op_shuffle_meat.hpp \
		armadillo_bits/op_prod_meat.hpp \
		armadillo_bits/op_pinv_meat.hpp \
		armadillo_bits/op_dotext_meat.hpp \
		armadillo_bits/op_flip_meat.hpp \
		armadillo_bits/op_princomp_meat.hpp \
		armadillo_bits/op_misc_meat.hpp \
		armadillo_bits/op_relational_meat.hpp \
		armadillo_bits/op_find_meat.hpp \
		armadillo_bits/op_chol_meat.hpp \
		armadillo_bits/op_cx_scalar_meat.hpp \
		armadillo_bits/op_trimat_meat.hpp \
		armadillo_bits/op_cumsum_meat.hpp \
		armadillo_bits/op_symmat_meat.hpp \
		armadillo_bits/op_hist_meat.hpp \
		armadillo_bits/op_unique_meat.hpp \
		armadillo_bits/op_toeplitz_meat.hpp \
		armadillo_bits/op_fft_meat.hpp \
		armadillo_bits/op_any_meat.hpp \
		armadillo_bits/op_all_meat.hpp \
		armadillo_bits/op_normalise_meat.hpp \
		armadillo_bits/op_clamp_meat.hpp \
		armadillo_bits/op_expmat_meat.hpp \
		armadillo_bits/op_nonzeros_meat.hpp \
		armadillo_bits/glue_times_meat.hpp \
		armadillo_bits/glue_mixed_meat.hpp \
		armadillo_bits/glue_cov_meat.hpp \
		armadillo_bits/glue_cor_meat.hpp \
		armadillo_bits/glue_kron_meat.hpp \
		armadillo_bits/glue_cross_meat.hpp \
		armadillo_bits/glue_join_meat.hpp \
		armadillo_bits/glue_relational_meat.hpp \
		armadillo_bits/glue_solve_meat.hpp \
		armadillo_bits/glue_conv_meat.hpp \
		armadillo_bits/glue_toeplitz_meat.hpp \
		armadillo_bits/glue_hist_meat.hpp \
		armadillo_bits/glue_histc_meat.hpp \
		armadillo_bits/glue_max_meat.hpp \
		armadillo_bits/glue_min_meat.hpp \
		armadillo_bits/spop_max_meat.hpp \
		armadillo_bits/spop_min_meat.hpp \
		armadillo_bits/spop_sum_meat.hpp \
		armadillo_bits/spop_strans_meat.hpp \
		armadillo_bits/spop_htrans_meat.hpp \
		armadillo_bits/spop_misc_meat.hpp \
		armadillo_bits/spop_mean_meat.hpp \
		armadillo_bits/spop_var_meat.hpp \
		armadillo_bits/spglue_plus_meat.hpp \
		armadillo_bits/spglue_minus_meat.hpp \
		armadillo_bits/spglue_times_meat.hpp \
		armadillo_bits/spglue_join_meat.hpp \
		armadillo_bits/compiler_setup_post.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.C

main.o: main.C mainwindow.H \
		formloadmatrix.H \
		ui_formLoadMatrix.h \
		formviewmatrix.H \
		ui_formMatrixView.h \
		formvariablesexogenas.h \
		stackwidget.H \
		accountwidget.H \
		stackvariablesexogenas.h \
		variableexogenawidget.h \
		formexportmatrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.C

formloadmatrix.o: formloadmatrix.C formloadmatrix.H \
		ui_formLoadMatrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formloadmatrix.o formloadmatrix.C

formviewmatrix.o: formviewmatrix.C formviewmatrix.H \
		ui_formMatrixView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formviewmatrix.o formviewmatrix.C

stackwidget.o: stackwidget.C stackwidget.H \
		accountwidget.H
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stackwidget.o stackwidget.C

accountwidget.o: accountwidget.C accountwidget.H
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o accountwidget.o accountwidget.C

formvariablesexogenas.o: formvariablesexogenas.cpp formvariablesexogenas.h \
		ui_formvariablesexogenas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formvariablesexogenas.o formvariablesexogenas.cpp

stackvariablesexogenas.o: stackvariablesexogenas.cpp stackvariablesexogenas.h \
		variableexogenawidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stackvariablesexogenas.o stackvariablesexogenas.cpp

variableexogenawidget.o: variableexogenawidget.cpp variableexogenawidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o variableexogenawidget.o variableexogenawidget.cpp

formexportmatrix.o: formexportmatrix.cpp formexportmatrix.h \
		ui_formexportmatrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formexportmatrix.o formexportmatrix.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_formloadmatrix.o: moc_formloadmatrix.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formloadmatrix.o moc_formloadmatrix.cpp

moc_formviewmatrix.o: moc_formviewmatrix.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formviewmatrix.o moc_formviewmatrix.cpp

moc_stackwidget.o: moc_stackwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_stackwidget.o moc_stackwidget.cpp

moc_accountwidget.o: moc_accountwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_accountwidget.o moc_accountwidget.cpp

moc_formvariablesexogenas.o: moc_formvariablesexogenas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formvariablesexogenas.o moc_formvariablesexogenas.cpp

moc_stackvariablesexogenas.o: moc_stackvariablesexogenas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_stackvariablesexogenas.o moc_stackvariablesexogenas.cpp

moc_variableexogenawidget.o: moc_variableexogenawidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_variableexogenawidget.o moc_variableexogenawidget.cpp

moc_formexportmatrix.o: moc_formexportmatrix.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formexportmatrix.o moc_formexportmatrix.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

