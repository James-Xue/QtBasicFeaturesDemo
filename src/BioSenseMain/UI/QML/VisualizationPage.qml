import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

Rectangle
{
    color: "transparent" // 或用浅色便于调试
    anchors.fill: parent

    Label
    {
        text: "可视化分析页面"
        font.pixelSize: 28
        anchors.centerIn: parent
        color: "#006064"
    }
}