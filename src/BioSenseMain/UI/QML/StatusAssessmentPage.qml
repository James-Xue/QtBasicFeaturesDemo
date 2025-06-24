import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle
{
    color: "transparent" // 或用浅色便于调试
    anchors.fill: parent

    Label
    {
        text: "状态评估页面"
        font.pixelSize: 28
        anchors.centerIn: parent
        color: "#006064"
    }
}