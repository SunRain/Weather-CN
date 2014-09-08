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

import "../js/lunar.js" as LunarHandler

Page {
    id: infopage
    
    property int screenWidth: Screen.width
    property int baseWidth: screenWidth/20
    property int baseHeight: screenWidth/20
    property int runningBusyIndicator: 1
    
    Loader{
        id:viewLoader
        anchors.fill: parent
        sourceComponent: busyIndicator
    }
    
    Component {
        id:errorPage
        
        SilicaFlickable {
            anchors.fill: parent
            
            PullDownMenu {
                MenuItem {
                    text: qsTr("About")
                }
                MenuItem {
                    text: qsTr("AddCity")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ProvincePage.qml"),
                                       {"locationProvider":locationProvider,
                                           "weatherProvider":weatherProvider})
                        locationProvider.startFetchProvince();
                    }
                }
            }
            
            contentHeight: Screen.height
            contentWidth: Screen.width
            
            Item{
                width: Screen.width
                height: Screen.height
                Label {
                    text: qsTr("Refresh error or no city added!")
                    anchors.centerIn: parent
                    color: Theme.highlightColor
                    Component.onCompleted: {
                        console.log("errorPage, on errorPage complete")
                    }
                }
            }
        }
    }
    
    Component {
        id:busyIndicator
        SilicaFlickable{
            anchors.fill: parent
            
            BusyIndicator{
                anchors.centerIn: parent
                size: BusyIndicatorSize.Large
                running: runningBusyIndicator != 0
                opacity: runningBusyIndicator != 0 ? 1: 0
                
                Component.onCompleted: {
                    console.log("busyIndicator completed!!!!!!!")
                    startFetchWeatherData();
                }
            }  
        }
    }
    
    Component{
        id:weatherView
        
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
                    onClicked: {
                        runningBusyIndicator = 1;
                    }
                }
            }
            
            // Tell SilicaFlickable the height of its content.
            contentHeight: column.height
            contentWidth: parent.width
            
            // Place our content in a Column.  The PageHeader is always placed at the top
            // of the page, followed by our content.
            Column {
                id: column
                width: parent.width
                spacing: Theme.paddingLarge
                
                Item {
                    id: headerBar
                    width: parent.width
                    height: Theme.fontSizeSmall*3
                    Label {
                        id: cityName
                        text: "CityName"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignBottom
                        color: Theme.primaryColor 
                        font.pixelSize:Theme.fontSizeSmall
                        anchors{
                            left: parent.left
                            leftMargin: baseWidth*3
                            top:parent.top
                            topMargin: Theme.fontSizeSmall
                        }
                        
                    }
                    
                    //TODO:由于目前是每次开启程序的时候都更新数据,没有缓存到本地,所以不需要在主界面显示是多久前更新的天气数据
                    /*Label {
                        id: updateTime
                        text: "updateTime"
                        height: cityName.height
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignBottom
                        anchors{
                            left: cityName.right
                            leftMargin: baseWidth *4
                            top:parent.top
                            topMargin: Theme.fontSizeSmall
                        }
                        color: Theme.primaryColor 
                        font.pixelSize:Theme.fontSizeTiny
                        
                    }*/
                }
                
                Item{
                    id: tempInfo
                    width: headerBar.width
                    height:Theme.fontSizeMedium * 13
                    
                    Item {
                        id: tempInfoLeft
                        width: (screenWidth - baseWidth)*2/3
                        height: parent.height
                        anchors.left: tempInfo.left
                        Label {
                            id: tempNum
                            anchors{
                                left: parent.left
                                leftMargin: baseWidth
                                top: parent.top
                                verticalCenterOffset: -baseWidth
                                verticalCenter: parent.verticalCenter
                            }
                            //text: "36"
                            font.pixelSize: Theme.fontSizeMedium * 10
                        }
                        
                        Label {
                            id: tempMaxMin
                            //text: "tempMaxMin"
                            anchors{
                                left: parent.left
                                top: tempNum.bottom
                                //topMargin: -baseHeight*2
                                leftMargin: baseWidth
                            }
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Theme.fontSizeSmall
                        }
                        
                        Label {
                            id: pm25
                            //text: "PM25Info"
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            anchors{
                                left: tempMaxMin.right
                                //leftMargin: baseWidth
                                top: tempNum.bottom
                            }
                            //anchors.topMargin: -baseHeight*2
                            font.pixelSize: Theme.fontSizeSmall
                        }
                    }
                    
                    Item {
                        id: tempInfoRight
                        width: parent.width - tempInfoLeft.width
                        height:tempInfoLeft.height
                        //color: "#199769"
                        //height: parent.height
                        anchors{
                            left: tempInfoLeft.right
                            leftMargin: baseWidth //tempInfoLeft.width + baseWidth
                            top: parent.top
                            //topMargin: baseHeight
                        }
                        
                        Label {
                            id: tempDot
                            anchors.top:parent.top
                            anchors.topMargin: baseWidth*2
                            text: "\u00b0"+"C"
                            font.pixelSize: Theme.fontSizeMedium*3
                        }
                        
                        Label {
                            id: currentWeatherInfo
                            //text: "currentWeatherInfo"
                            anchors.top: tempDot.bottom
                            anchors.topMargin: baseHeight
                            font.pixelSize: Theme.fontSizeMedium
                        }
                        
                        Label {
                            id: date
                            //text: "date"
                            anchors.top: currentWeatherInfo.bottom
                            anchors.topMargin: baseHeight
                            font.pixelSize: Theme.fontSizeMedium
                        }
                        
                        Label {
                            id: lunar
                            anchors.top:date.bottom
                            anchors.topMargin: baseHeight
                            //text: "lunar"
                            font.pixelSize: Theme.fontSizeMedium
                        }
                    }
                }
                
                /*
                 *Adjust by the image size
                 */
                Item {
                    id:weatherIconInfo
                    width: headerBar.width
                    height: 315

                    //TODO:need to fit the icon size
                    Item{
                        id:leftArrow
                        width: 72
                        height: parent.height

                        anchors.top: parent.top
                        anchors.left: parent.left
                        
                        //(540-300-72*2)/4
                        anchors.leftMargin: (screenWidth-300-72*2)/4//48//baseWidth*3
                        
                        Image {
                            //size: 32*32
                            //id: leftArrow
                            anchors.centerIn: parent
                            source: "../images/left_arrow.png"
                            
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("leftArrow clicked!!!! ")
                                }
                            }
                        }
                    }
                    
                    Item{
                        id:weatherIcon
                        width: 300
                        height: parent.height
                        //color: "#144971"
                        
                        anchors.left: leftArrow.right
                        anchors.top:parent.top
                        anchors.leftMargin: (screenWidth-300-72*2)/4//48
                        
                        Image {
                            id:weatherIconImage
                            anchors.centerIn: parent
                            //source: "../images/w4.png"
                        }
                    }
                    
                    Item{
                        id:rightArrow
                        width: 72
                        height: parent.height

                        anchors.left: weatherIcon.right
                        anchors.top: parent.top
                        anchors.leftMargin:(screenWidth-300-72*2)/4// 48
                        
                        Image {
                            //size:32*32
                            anchors.centerIn: parent
                            source: "../images/right_arrow.png"
                            
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("reight arrow clicked!!!!")
                                }
                            }
                        }
                    }
                    
                }
                
                Item{
                    id: lifeInfo
                    
                    width: headerBar.width
                    height: 400
                    
                    Label {
                        id:kongtiao
                        anchors.top: parent.top
                        
                        color: "#00FF00"
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
            /*Component.onCompleted: {
                console.log("=========== weather view finished")
                cityName.text = weatherProvider.weatherModel.areaName;
            }*/
        }
    }
    Connections {
        target: weatherProvider
        onFetchWeatherDataFailed: {
            console.log("fetch weather data failed");
            
            runningBusyIndicator = 0;
            
            viewLoader.sourceComponent = errorPage;
            
        }
        
        onFetchWeatherDataSucceed: {
            console.log("fetch weather data succeed");
            runningBusyIndicator = 0;
            
            viewLoader.sourceComponent = weatherView;
            
            setWeatherData();
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
    
    function startFetchWeatherData() {
        weatherProvider.startFetchWeatherData("");
    }
    
    function setWeatherData() {
        //TODO:由于目前是每次开启程序的时候都更新数据,没有缓存到本地,所以不需要在主界面显示是多久前更新的天气数据
       //var lastUpdateTime = Math.round(new Date().getTime()/1000);
        cityName.text = weatherProvider.weatherModel.areaName;
    }
}


