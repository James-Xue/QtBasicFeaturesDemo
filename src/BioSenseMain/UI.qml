// 示例：现代登录界面
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: window
    width: 400
    height: 500
    title: "Modern Login"
    color: "#f5f7fa"
    visible: true

    // 主内容卡片
    Rectangle {
        id: loginCard
        width: parent.width * 0.8
        height: parent.height * 0.7
        radius: 12
        color: "white"
        anchors.centerIn: parent
        elevation: 5  // 阴影效果

        // 标题
        Text {
            id: titleText
            text: "Welcome Back"
            font.family: "Inter"
            font.pixelSize: 28
            font.bold: true
            color: "#333333"
            anchors {
                top: parent.top
                topMargin: 40
                horizontalCenter: parent.horizontalCenter
            }
        }

        // 输入框
        Column {
            spacing: 20
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: 40
                rightMargin: 40
                top: titleText.bottom
                topMargin: 40
            }

            TextField {
                id: usernameField
                placeholderText: "Username"
                font.pixelSize: 16
                height: 40
                background: Rectangle {
                    color: "#f0f2f5"
                    radius: 8
                    border.color: usernameField.hasFocus ? "#4a89dc" : "#e0e0e0"
                    border.width: 1
                }
                padding.left: 12
            }

            TextField {
                id: passwordField
                placeholderText: "Password"
                font.pixelSize: 16
                height: 40
                echoMode: TextInput.Password
                background: Rectangle {
                    color: "#f0f2f5"
                    radius: 8
                    border.color: passwordField.hasFocus ? "#4a89dc" : "#e0e0e0"
                    border.width: 1
                }
                padding.left: 12
            }
        }

        // 登录按钮
        Button {
            id: loginButton
            text: "Sign In"
            font.pixelSize: 16
            width: parent.width * 0.6
            height: 45
            radius: 22
            color: "#4a89dc"
            highlighted: true
            hoverEnabled: true
            onClicked: console.log("Login clicked")
            anchors {
                bottom: parent.bottom
                bottomMargin: 40
                horizontalCenter: parent.horizontalCenter
            }

            // 悬停效果
            states: State {
                name: "hovered"
                when: hovered
                PropertyChanges {
                    target: loginButton
                    color: "#3a7bd5"
                    scale: 1.05
                }
            }
            transitions: Transition {
                from: ""
                to: "hovered"
                reversible: true
                NumberAnimation { properties: "scale,color"; duration: 150 }
            }
        }
    }

    // 底部文本
    Text {
        id: footerText
        text: "Don't have an account? Sign Up"
        font.pixelSize: 14
        color: "#666666"
        anchors {
            bottom: parent.bottom
            bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: console.log("Sign up clicked")
        }
    }
}
