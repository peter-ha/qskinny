TEMPLATE = subdirs

# c++
SUBDIRS += \
    compositing-controls \
    control-with-skinlet \
    desktop \
    grid-layout \
    horizontal-layout \
    layouts \
    listbox \
    messagebox \
    mycontrols \
    nesting-layouts \
    scalable-graphics \
    scene-graph-nodes \
    size-hints \
    size-policies \
    sliders \
    stack-layout \
    stretch-factors \
    subclassing-existing-control \
    thumbnails \
    tabview \
    vertical-layout

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
