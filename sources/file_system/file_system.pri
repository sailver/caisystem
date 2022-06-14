SOURCES += \
    $$PWD/CaiDirectory.cpp \
    $$PWD/huffman.cpp \
    $$PWD/decode.cpp \
    $$PWD/encode.cpp \

HEADERS += \
    $$PWD/CaiDirectory.h \
    $$PWD/HT.h \
    $$PWD/huffman.h

# 不要用 /*.cpp 这类方法，会报错，不知道为什么

DISTFILES += \
    $$PWD/ht.txt
