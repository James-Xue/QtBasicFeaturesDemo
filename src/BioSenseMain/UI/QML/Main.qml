import QtQml 6.9
import QtQuick.Window 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import "qrc:/QML"

Window
{
    id: mainWindow
    width: 1200
    height: 900
    visible: true
    title: qsTr("生理评估软件") // "BioSense Main Window"
    color: "#dae8f9"           // 主背景色 RGB(218,232,249)

    // 设置控件风格，必须这样写
    // Component.onCompleted:
    // {
    //     Qt.callLater(function() { QtQuick.Controls.Style.style = "Fusion" })
    // }

    // 顶部区域：大字标题 + 搜索框
    Rectangle
    {
        id: topBarBg
        color: "#daeefd" // 顶部栏背景色 RGB(218,238,253)
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        Row
        {
            id: topBar
            spacing: 20
            anchors.fill: parent
            anchors.margins: 20

            Image
            {
                source: "qrc:/Icon/AppIcon.png"
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
            }

            Text
            {
                text: "生理评估软件"
                font.pixelSize: 32
                font.bold: true
                color: "#006064"
                anchors.verticalCenter: parent.verticalCenter
            }

            // 改为使用 SearchBar 组件
            SearchBar
            {
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    // 主体区域：左侧竖直页签 + 折叠按钮 + 右侧内容
    RowLayout
    {
        anchors.top: topBarBg.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        spacing: 0

        // 折叠时按钮在最左侧
        Rectangle
        {
            id: collapseBtnLeft
            visible: sideTabBar.collapsed
            width: 20
            Layout.fillHeight: true
            color: "#b0c4de"
            border.color: "#90a4ae"
            border.width: 1

            MouseArea
            {
                anchors.fill: parent
                onClicked: sideTabBar.collapsed = !sideTabBar.collapsed
            }
            Text
            {
                anchors.centerIn: parent
                text: ">"
                font.pixelSize: 18
            }
        }

        SideTabBar
        {
            id: sideTabBar
            // 可通过 sideTabBar.currentIndex 获取当前选中页签
            Layout.preferredWidth: sideTabBar.collapsed ? 40 : 180
            Layout.fillHeight: true
        }

        // 展开时按钮在中间
        Rectangle
        {
            id: collapseBtnRight
            visible: !sideTabBar.collapsed
            width: 20
            Layout.fillHeight: true
            color: "#b0c4de"
            border.color: "#90a4ae"
            border.width: 1

            MouseArea
            {
                anchors.fill: parent
                onClicked: sideTabBar.collapsed = !sideTabBar.collapsed
            }
            Text
            {
                anchors.centerIn: parent
                text: "<"
                font.pixelSize: 18
            }
        }

        MainContentArea
        {
            currentIndex: sideTabBar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    // 关闭事件
    onClosing:
    {
        console.log("BioSense application is closing")
    }
}
