import QtQuick
import QtQuick.Controls

Button
{
    id: tabButton
    property string label: ""
    text: label
    checkable: true
    width: 160
    height: 56
    font.pixelSize: 22
    background: Rectangle
    {
        color: checked ? "#c0def9" : "#d0e9fd"
        radius: 8
    }
    contentItem: Text
    {
        text: tabButton.text
        color: "#006064"
        font.pixelSize: 22
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
    }
}
