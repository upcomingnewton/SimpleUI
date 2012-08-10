 CONFIG      += uitools

 HEADERS     = sKDE.h \
               sKdeCallbacks/sKde_Cb.h \
               ../../misc/misc.h
 RESOURCES   = sKde.qrc
 SOURCES     = sKde.cpp \
               main.cpp \
               KdeCallbacks/sKde_Cb.cpp 
 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/designer/calculatorbuilder
 sources.files = $$SOURCES $$HEADERS $$RESOURCES *.ui *.pro
 sources.path = $$[QT_INSTALL_EXAMPLES]/designer/calculatorbuilder
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
