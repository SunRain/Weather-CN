/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

import com.sunrain.magicweather 1.0

Page {
    id: infopage

    property int screenWidth: Screen.width
   // property int screenHeight: 960
    property int baseWidth: screenWidth/20
    property int baseHeight: screenWidth/20
    //property int baseHeight: 20

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        id:main
        anchors.fill: parent


        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
            }
            MenuItem {
                text: qsTr("AddCity")
                onClicked: {
                    //locationProvider.startFetchProvince();
                    pageStack.push(Qt.resolvedUrl("ProvincePage.qml"),
                                   {"locationProvider":locationProvider,
                                    "weatherProvider":weatherProvider})
                    locationProvider.startFetchProvince();
                }
            }
            MenuItem {
                text: qsTr("Refresh")
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height
        contentWidth: parent.width
        //VerticalScrollDecorator{
        //    flickable:main
        //}

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge
            /*PageHeader {
                title: qsTr("UI Template")
            }*/
            Rectangle {
                id: headerBar
                color: "#a05b38"
                border.color: "#423c3c"
                width: parent.width//screenWidth - baseWidth*2
                height: Theme.fontSizeSmall*3
                    Label {
                        id: cityName
                        text: "CityName"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignBottom
                        anchors.left: parent.left
                        anchors.leftMargin: baseWidth*3
                        anchors.top:parent.top
                        anchors.topMargin: Theme.fontSizeSmall
                        font.pixelSize:Theme.fontSizeSmall
                    }
                    Label {
                        id: updateTime
                        text: "updateTime"
                        height: cityName.height
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignBottom
                        anchors.left: cityName.right
                        anchors.leftMargin: baseWidth *4
                        anchors.top:parent.top
                        anchors.topMargin: Theme.fontSizeSmall
                        font.pixelSize:Theme.fontSizeTiny
                    }
            }

            Rectangle{
                id: tempInfo
                width: headerBar.width
                height:Theme.fontSizeMedium * 13
                color: "#7a6a55"
                //anchors.topMargin: baseHeight
                Rectangle {
                    id: tempInfoLeft
                    //y: 0
                    width: (screenWidth - baseWidth)*2/3//tempNum.width + baseWidth
                    height: parent.height//tempNum.height + tempMaxMin.height
                    //anchors.top:tempInfo.top
                    anchors.left: tempInfo.left
                    color: "#ee1414"
                    Label {
                        id: tempNum
                        anchors.left: parent.left
                        anchors.leftMargin: baseWidth
                        anchors.top: parent.top
                        text: "36"
                        anchors.verticalCenterOffset: -baseWidth
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: Theme.fontSizeMedium * 10
                    }

                    Label {
                        id: tempMaxMin
                        text: "tempMaxMin"
                        anchors.left: parent.left
                        anchors.top: tempNum.bottom
                        //anchors.topMargin: -baseHeight*2
                        anchors.leftMargin: baseWidth
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: Theme.fontSizeSmall
                    }

                    Label {
                        id: pm25
                        text: "PM25Info"
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: tempMaxMin.right
                        //anchors.leftMargin: baseWidth
                        anchors.top: tempNum.bottom
                        //anchors.topMargin: -baseHeight*2
                        font.pixelSize: Theme.fontSizeSmall
                    }
                }

                Rectangle {
                    id: tempInfoRight
                    width: parent.width - tempInfoLeft.width
                    height:tempInfoLeft.height
                    color: "#199769"
                    //height: parent.height
                    anchors.left: tempInfoLeft.right
                    anchors.leftMargin: baseWidth //tempInfoLeft.width + baseWidth
                    anchors.top: parent.top
                    //anchors.topMargin: baseHeight

                    Label {
                        id: tempDot
                        anchors.top:parent.top
                        anchors.topMargin: baseWidth*2
                        text: "\u00b0"+"C"
                        font.pixelSize: Theme.fontSizeMedium*3
                    }

                    Label {
                        id: currentWeatherInfo
                        text: "currentWeatherInfo"
                        anchors.top: tempDot.bottom
                        anchors.topMargin: baseHeight
                        font.pixelSize: Theme.fontSizeMedium
                    }

                    Label {
                        id: date
                        text: "date"
                        anchors.top: currentWeatherInfo.bottom
                        anchors.topMargin: baseHeight
                        font.pixelSize: Theme.fontSizeMedium
                    }

                    Label {
                        id: lunar
                        anchors.top:date.bottom
                        anchors.topMargin: baseHeight
                        text: "lunar"
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }
            }

            //TODO:need to fit the icon size

            Rectangle {
                id:weatherIconInfo
                width: headerBar.width
                height: 200
                color: "#2114db"

                //TODO:need to fit the icon size

                Rectangle{
                    id:leftArrow
                    width: baseWidth*5
                    height: parent.height
                    color: "#ad3030"

                    anchors.top: parent.top
                    anchors.left: parent.left

                    anchors.leftMargin: baseWidth*3

                    Image {
                        //id: leftArrow
                        source: "../images/left_arrow.png"
                    }
                }

                Rectangle{
                    id:weatherIcon
                    width: baseWidth*5
                    height: parent.height
                    color: "#144971"

                    anchors.left: leftArrow.right
                    anchors.top:parent.top

                    Image {
                        //id: weatherIcon
                        source: "../images/w17.png"
                    }
                }

                Rectangle{
                    id:rightArrow
                    width: baseWidth*5
                    height: parent.height
                    color: "#ee1818"

                    anchors.left: weatherIcon.right
                    anchors.top: parent.top

                    Image {
                        source: "../images/right_arrow.png"
                    }
                }

            }

            /*Rectangle{
                id: lifeInfo

                width: headerBar.width
                height: 400
                color: "#13db92"
                */

                Label {
                    id:kongtiao
                    anchors.top: parent.top

                     color: "#00FF00"


                    //textFormat: Text.RichText

                    text: "kongtiao\nInfo ..............."
                }
                Label {
                    id: yundong
                    anchors.top: kongtiao.bottom

                    color: "steelblue"

                    text: "yundong\nInfo ............"
                }
                Label {
                    id:ziwaixian
                    anchors.top: yundong.bottom

                    text: "ziwaixian\nInfo..............."
                }
                Label {
                    id:ganmao
                    anchors.top:ziwaixian.bottom

                    color: "steelblue"

                    text: "ganmao\nInfo ......."
                }
                Label {
                    id: xiche
                    anchors.top: ganmao.bottom

                    text: "xiche"
                }
                Label {
                    id:wuran
                    anchors.top:xiche.bottom

                    color: "steelblue"

                    text: "wuran"
                }
                Label {
                    id: chuanyi
                    anchors.top: wuran.bottom

                    color: "steelblue"

                    text: "chuanyi"
                }
            }

        }
    }

    Connections {
        target: weatherProvider
        onFetchWeatherDataFailed: {
            console.log("fetch weather data failed");

        }

        onFetchWeatherDataSucceed: {
            console.log("fetch weather data succeed");
            //weatherProvider.weatherModel
            console.log(weatherProvider.weatherModel.weatherObjectList[1])
            console.log(weatherProvider.weatherModel.currentWeatherModel.info)


        }
    }

    LocationProvider {
        id: locationProvider
    }

    WeatherProvider {
        id: weatherProvider
    }

    WeatherObjectModel {
        id: weatherObjectModel
    }

    CurrentWeatherModel {
        id: currentWeatherModel
    }
}


