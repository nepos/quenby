import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.1

InputPanel {
    id: inputPanel

    signal activated(bool a)
    signal heightChanged(int h)

    onActiveChanged: activated(active)
    onHeightChanged: heightChanged(height)
}

