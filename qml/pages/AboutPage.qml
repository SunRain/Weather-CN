import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: aboutpage
        
    SilicaFlickable {
        anchors.fill: parent
        
        contentHeight: column.height
        //contentWidth: column.width
        
        Column {
            id:column
            PageHeader {
                title: qsTr("About Weather")
            }

            spacing: Theme.paddingSmall

            width: parent.width

            //header
            Item {
                height: aboutWeather.height
                anchors { 
                    left: parent.left
                    right: parent.right 
                }
                Label {
                    id:aboutWeather
                    anchors{
                        centerIn: parent
                     }
                    color: Theme.highlightColor
                    font.pixelSize: Theme.fontSizeHuge
                    wrapMode: Text.Wrap
                    text: qsTr("ChineseWeather")
                }
            }
            
            Item {
                height: aboutInfo.height
                anchors { 
                    left: parent.left
                    right: parent.right 
                }
                Label {
                    id:aboutInfo
                    anchors {
                        centerIn: parent
                    }
                    color: Theme.primaryColor
                    font.pixelSize: Theme.fontSizeLarge
                    wrapMode: Text.Wrap
                    text: qsTr("Written by learning qml")
                }
            }
            
            //author info
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                }
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                width: parent.width - (2 * Theme.paddingLarge)
                wrapMode: Text.Wrap
                text: qsTr("Author:wanggjghost")//作者:wanggjghost(泪の单翼天使)
            }
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                }
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                wrapMode: Text.Wrap
                width: parent.width - (2 * Theme.paddingLarge)
                text: qsTr("E-mail:41245110@qq.com")//作者:wanggjghost(泪の单翼天使)
            }
            
            BackgroundItem {
                //id: clickableUrl
                contentHeight: authorGithub.height
                height: contentHeight
                width: parent.width
                anchors {
                    left: parent.left
                }
                Label {
                    id: authorGithub
                    anchors {
                        left: parent.left
                        margins: Theme.paddingLarge
                    }
                    wrapMode: Text.Wrap
                    width: parent.width - (2 * Theme.paddingLarge)
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("Github: https://github.com/SunRain/Weather-CN")
                    color: authorGithub.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
                onClicked: {
                    openUrl("https://github.com/SunRain/Weather-CN");
                }
            }
            
            Separator {
                width:parent.width;
                color: Theme.highlightColor
            }
            
            //credit label
            Item {
                height: creditLabel.height
                anchors { 
                    left: parent.left
                    right: parent.right 
                }
                Label {
                    id:creditLabel
                    anchors{
                        centerIn: parent
                    }
                    color: Theme.highlightColor
                    font.pixelSize: Theme.fontSizeLarge
                    text: qsTr("Credit")
                }
            }
            
            //FineDay
            Item{
                height: fineDayLabel.height
                anchors { 
                    left: parent.left
                    right: parent.right 
                }
                Label {
                    id:fineDayLabel
                    anchors{
                        centerIn: parent
                    }
                    color: Theme.highlightColor
                    font.pixelSize: Theme.fontSizeMedium
                    text: qsTr("FineDay")
                }
            }
            
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                }
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                width: parent.width - (2 * Theme.paddingLarge)
                wrapMode: Text.Wrap
                text: qsTr("Author:sd6352051")
            }
            
            BackgroundItem {
                //id: clickableUrl
                contentHeight: finedayGithub.height
                height: contentHeight
                width: parent.width
                anchors {
                    left: parent.left
                }
                Label {
                    id: finedayGithub
                    anchors {
                        left: parent.left
                        margins: Theme.paddingLarge
                    }
                    wrapMode: Text.Wrap
                    width: parent.width - (2 * Theme.paddingLarge)
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("Github: https://github.com/sd6352051")
                    color: finedayGithub.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
                onClicked: {
                    openUrl("https://github.com/sd6352051");
                }
            }
            
            //Js Lunar
            Item{
                height: jsLunarLabel.height
                anchors { 
                    left: parent.left
                    right: parent.right 
                }
                Label {
                    id:jsLunarLabel
                    anchors{
                        centerIn: parent
                    }
                    color: Theme.highlightColor
                    font.pixelSize: Theme.fontSizeMedium
                    text: qsTr("JS Lunar")
                }
            }
            
            Label {
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                }
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                width: parent.width - (2 * Theme.paddingLarge)
                wrapMode: Text.Wrap
                text: qsTr("Author:FlyingFishBird")
            }
            
            BackgroundItem {
                contentHeight: jsGithub.height
                height: contentHeight
                width: parent.width
                anchors {
                    left: parent.left
                }
                Label {
                    id: jsGithub
                    anchors {
                        left: parent.left
                        margins: Theme.paddingLarge
                    }
                    wrapMode: Text.Wrap
                    width: parent.width - (2 * Theme.paddingLarge)
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("Github: https://github.com/FlyingFishBird")
                    color: jsGithub.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
                onClicked: {
                    openUrl("https://github.com/FlyingFishBird");
                }
            }
        }
    }
    
    function openUrl(url) {
        Qt.openUrlExternally(url)
    }
}
