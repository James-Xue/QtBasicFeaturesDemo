import QtQuick
import QtQuick.Layouts

Rectangle
{
    color: "#ffffff"
    radius: 12
    border.color: "#d0e9fd"
    border.width: 1
    Layout.fillWidth: true
    Layout.fillHeight: true

    // 传入当前选中索引
    property int currentIndex: 0

    StackLayout
    {
        id: stack
        anchors.fill: parent
        currentIndex: parent.currentIndex

        Loader { source: "qrc:/QML/DataImportPage.qml" }
        Loader { source: "qrc:/QML/SignalPreprocessPage.qml" }
        Loader { source: "qrc:/QML/FeatureExtractPage.qml" }
        Loader { source: "qrc:/QML/VisualizationPage.qml" }
        Loader { source: "qrc:/QML/StatusAssessmentPage.qml" }
        Loader { source: "qrc:/QML/DataSavePage.qml" }
    }
}