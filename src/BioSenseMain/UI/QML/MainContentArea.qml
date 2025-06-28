import QtQuick 6.9
import QtQuick.Layouts 6.9

// 主内容区组件，负责根据左侧页签切换显示不同的功能页面
Rectangle
{
    color: "#ffffff"           // 内容区背景色
    radius: 12                 // 圆角
    border.color: "#d0e9fd"    // 边框颜色
    border.width: 1            // 边框宽度
    Layout.fillWidth: true     // 横向填充父布局
    Layout.fillHeight: true    // 纵向填充父布局

    // 当前选中的页签索引，由外部传入
    property int currentIndex: 0

    // 堆叠布局，根据 currentIndex 切换显示不同页面
    StackLayout
    {
        id: stack
        anchors.fill: parent
        currentIndex: parent.currentIndex

        // 各功能页面，按顺序与侧边栏页签一一对应
        Loader { source: "qrc:/QML/DataImportPage.qml" }          // 数据导入
        Loader { source: "qrc:/QML/SignalPreprocessPage.qml" }    // 信号预处理
        Loader { source: "qrc:/QML/FeatureExtractPage.qml" }      // 特征提取
        Loader { source: "qrc:/QML/VisualizationPage.qml" }       // 可视化分析
        Loader { source: "qrc:/QML/StatusAssessmentPage.qml" }    // 状态评估
        Loader { source: "qrc:/QML/DataSavePage.qml" }            // 数据保存
    }
}