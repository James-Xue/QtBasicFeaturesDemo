import QtQml
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import "qrc:/QML"

Window
{
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: "BioSense Main Window"
    color: "#dae8f9" // 主背景色 RGB(218,232,249)

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

    // 主体区域：左侧竖直页签 + 右侧内容
    RowLayout
    {
        anchors.top: topBarBg.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        spacing: 20

        // 竖直页签
        Column
        {
            id: verticalTabs
            spacing: 16
            Layout.preferredWidth: 180
            Layout.fillHeight: true

            property int currentIndex: 0

            Repeater
            {
                model: [
                    "数据导入",
                    "信号预处理",
                    "特征提取",
                    "可视化分析",
                    "状态评估",
                    "数据保存"
                ]
                delegate: TabButton
                {
                    label: modelData
                    checked: (verticalTabs.currentIndex === index)
                    onClicked: verticalTabs.currentIndex = index
                    width: parent.width
                }
            }
        }

        // 右侧内容区
        Rectangle
        {
            color: "#ffffff"
            radius: 12
            border.color: "#d0e9fd" // 内容区边框
            border.width: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout
            {
                id: stack
                anchors.fill: parent
                currentIndex: verticalTabs.currentIndex

                // 使用资源路径加载界面
                Loader { source: "qrc:/QML/DataImportPage.qml" }
                Loader { source: "qrc:/QML/SignalPreprocessPage.qml" }
                Loader { source: "qrc:/QML/FeatureExtractPage.qml" }
                Loader { source: "qrc:/QML/VisualizationPage.qml" }
                Loader { source: "qrc:/QML/StatusAssessmentPage.qml" }
                Loader { source: "qrc:/QML/DataSavePage.qml" }
            }
        }
    }

    // 关闭事件
    onClosing:
    {
        console.log("BioSense application is closing")
    }
}
