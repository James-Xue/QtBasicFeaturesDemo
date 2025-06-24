import QtQuick
import QtQuick.Controls

Button
{
    }
    id: tabButton
    // 声明一个可写的字符串属性 label
    property string label: ""

    // 将 button 的 text 绑定到 label
    text: label

    checkable: true
    width: parent.width
    height: 56
    background: Rectangle
    {
        color: checked ? "#c0def9" : "#d0e9fd"
        radius: 8
    }
}
