import QtQuick 2.0

Rectangle {
    id: base
    width: 540
    height: 940
    color: "#ffffff"
    opacity: 1

    property int screenWidth: 540
    property int screenHeight: 960
    property int baseWidth: 20
    property int baseHeight: 20

    Row {
        id: headerBar
        x: baseWidth
        y: baseWidth
        width: screenWidth - baseWidth*2
        height: baseWidth*3
        anchors.right: parent.right
        anchors.rightMargin: 13
        anchors.left: parent.left
        anchors.leftMargin: 17
        anchors.top: parent.top
        anchors.topMargin: 28
        opacity: 1

        Text {
            id: cityName
            //y: 8
            width: baseWidth*8
            height: baseWidth*2
            text: "CityName"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignBottom
            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: baseWidth *2
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }

        Text {
            id: updateTime
            //x: 271
            //y: 8
            width: cityName.width
            height: cityName.height
            text: "updateTime"
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
            anchors.right:  parent.right
            anchors.rightMargin: baseWidth*3
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }
    }

    Row {
        id: tempInfo
        x: headerBar.x
        y: 108
        //y: 108
        //y: 0
        width: headerBar.width
        height: baseHeight*20
        spacing: 0
        anchors.topMargin: 20
        anchors.top: headerBar.bottom

        Column {
            id: tempInfoLeft
            y: 0
            width: 305
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 20

            Text {
                id: tempNum
                x: 24
                y: 38
                width: 258
                height: 271
                text: qsTr("Text")
                anchors.verticalCenterOffset: -20
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }

            Text {
                id: tempMaxMin
                width: 130
                height: 49
                text: qsTr("tempMaxMin")
                anchors.top: tempNum.bottom
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 12
            }

            Text {
                id: pm25
                width: 127
                height: 49
                text: qsTr("pm25info")
                horizontalAlignment: Text.AlignRight
                anchors.left: tempMaxMin.right
                anchors.leftMargin: 20
                anchors.top: tempNum.bottom
                anchors.topMargin: 20
                font.pixelSize: 12
            }
        }

        Column {
            id: tempInfoRight
            x: 337
            y: 46
            width: 150
            height: 308

            Text {
                id: tempDot
                x: 0
                y: 0
                width: parent.width
                height: 66
                text: qsTr("Text")
                font.pixelSize: 12
            }

            Text {
                id: currentWeatherInfo
                x: 0
                width: parent.width
                height: 64
                text: qsTr("Text")
                anchors.top: tempDot.bottom
                anchors.topMargin: 10
                font.pixelSize: 12
            }

            Text {
                id: date
                x: 0
                width: parent.width
                height: 65
                text: qsTr("Text")
                anchors.top: currentWeatherInfo.bottom
                anchors.topMargin: 10
                font.pixelSize: 12
            }

            Text {
                id: lunar
                x: 0
                y: 233
                width: parent.width
                height: 53
                text: qsTr("Text")
                font.pixelSize: 12
            }
        }


    }

    Row {
        id: weatherIconInfo
        x: 17
        y: 528
        width: 510
        height: 256
        spacing: 20
        anchors.top: tempInfo.bottom
        anchors.topMargin: 20

        Image {
            id: leftArrow
            y: 8
            width: 100
            height: 240
            anchors.left: parent.left
            anchors.leftMargin: 20
            source: "qrc:/qtquickplugin/images/template_image.png"
        }

        Image {
            id: weatherIcon
            x: 170
            y: 8
            width: 201
            height: 240
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.TileVertically
            source: "../images/w1_s.png"
        }

        Image {
            id: rightArrow
            x: 402
            y: 8
            width: 100
            height: 240
            anchors.right: parent.right
            anchors.rightMargin: 20
            source: "qrc:/qtquickplugin/images/template_image.png"
        }
    }

    Column {
        id: lifeInfo
        x: 17
        y: 804
        width: 510
        height: 254
        anchors.top: weatherIconInfo.bottom
        anchors.topMargin: 20

        Text {
            id: pmAdvice
            x: 0
            y: 0
            width: 510
            height: 61
            text: qsTr("Text")
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 12
        }

        Text {
            id: kongtiao
            x: 0
            y: 67
            width: 510
            height: 57
            text: qsTr("Text")
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 12
        }
    }
}
