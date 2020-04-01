TEMPLATE = subdirs

# c++
SUBDIRS += \
    desktop \
    layouts \
    listbox \
    messagebox \
    mycontrols \
    sliders \
    thumbnails \
    tabview

SUBDIRS += \
    documentation/animations \
    documentation/compositing-controls \
    documentation/control-with-skinlet \
    documentation/grid-layout \
    documentation/horizontal-layout \
    documentation/nesting-layouts \
    documentation/scalable-graphics \
    documentation/scene-graph-nodes \
    documentation/size-hints \
    documentation/size-policies \
    documentation/skin-factory \
    documentation/stack-layout \
    documentation/stretch-factors \
    documentation/subclassing-existing-control \
    documentation/switching-skinlets \
    documentation/vertical-layout


qtHaveModule(svg) {

    # when checking in qvg files we could drop the svg dependency 

    SUBDIRS += \
        automotive \
        qvgviewer
}

# qml
SUBDIRS += \
    boxes \
    buttons \
    colorswitch \
    frames \
    gbenchmark \
    glabels \
    messageboxQml \
    tlabels
