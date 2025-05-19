import QtQml
import QtQuick.Window
import QtQuick.Controls

Window {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: "BioSense Main Window"

    // Include the main application component
    Component.onCompleted: {
        console.log("BioSense application started")
    }

    // Load the main application QML file
    Loader {
        id: appLoader
        source: "BioSenseApp.qml"
        anchors.fill: parent
    }

    // Handle window close event
    onClosing: {
        console.log("BioSense application is closing")
    }
}
