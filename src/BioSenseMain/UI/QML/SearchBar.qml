import QtQuick 6.9
import QtQuick.Controls 6.9

Rectangle
{
    id: searchBar
    width: 300
    height: 36
    radius: 6
    color: "#ffffff"
    border.color: "transparent"
    border.width: 0

    Row
    {
        anchors.fill: parent
        spacing: 5

        Image
        {
            source: "qrc:/Icon/SearchIcon.png"
            width: 20
            height: 20
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
        }

        Text
        {
            text: "搜索..."
            color: "#999999"
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}