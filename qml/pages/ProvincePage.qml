import QtQuick 2.0
import Sailfish.Silica 1.0

import com.sunrain.magicweather 1.0

Page {
    id: provincepage
    property string searchString
    property int runningBusyIndicator: 1
    property string clickedCityID: "-1"
    property string clickItemDisplayName: ""
    
    property LocationProvider locationProvider
    property WeatherProvider weatherProvider
    
    
    signal signalBusyIndicatorHide()
    
    onSignalBusyIndicatorHide: {
        console.log("aaaa qml -- onSignalBusyIndicatorHide");
    }
    
    /*Component.onCompleted: {
        console.log("aaaa qml -- on Province Page Completed");
        locationProvider.startFetchProvince();
    }*/
    
    Loader {
        id:pageLoader
        anchors.fill: parent
    }
    
    BusyIndicator {
        id: busyIndicator
        running: runningBusyIndicator != 0
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        opacity: runningBusyIndicator != 0 ? 1: 0
        
        Behavior on opacity {
            FadeAnimation {}
        }
    }
    
    Component {
        id:errorPage
        Column {
            id: headerContainer
            width: provincepage.width
            spacing: 10
            anchors.fill: parent
            PageHeader {
                id:pageHeader
                title: qsTr("error")
            }
            
            Label {
                parent: headerContainer
                //anchors.fill: parent
                
                text: qsTr("error page !")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                
                Component.onCompleted: {
                    console.log("errorPage, on errorPage complete")
                }
            }
        }
    }
    
    Component {
        id: listViewComponent
        Column {
            id: headerContainer
            width: provincepage.width
            //anchors.fill: parent
            spacing: Theme.paddingSmall
            
            PageHeader {
                id:pageHeader
                title: qsTr("Province")
            }
            
            //id: listViewComponent
            SilicaListView {
                anchors.fill: parent
                width: parent.width
                currentIndex: -1 // otherwise currentItem will steal focus
                
                header:  Item {
                    id: header
                    width: parent.width//provincepage.width//.width
                    height: pageHeader.height//headerContainer.height//provincepage.height//headerContainer.height
                    
                    Component.onCompleted: {
                        headerContainer.parent = header
                        console.log("listViewComponet, on header complete")
                    }
                }
                
                model: locationProvider.getProvinceList
                
                delegate: BackgroundItem{
                    Label {
                        textFormat: Text.StyledText
                        text: model.modelData.displayText
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: Theme.paddingLarge
                        }
                    }
                    
                    onClicked: {
                        clickedCityID = model.modelData.id
                        clickItemDisplayName = model.modelData.displayText
                        //locationProvider.setCityId(clickedCityID);
                        console.log("click item num <" + clickedCityID +">")
                        console.log(model.modelData.displayText)

                        pageStack.push(Qt.resolvedUrl("CityPage.qml"),{
                                           "clickedCityID":clickedCityID,
                                           "clickItemDisplayName":clickItemDisplayName,
                                           "locationProvider":locationProvider,
                                           "weatherProvider":weatherProvider})
                        
                        locationProvider.startFetchCity(clickedCityID,clickItemDisplayName)
                    }
                }
                
                VerticalScrollDecorator {}
                
                Component.onCompleted: {
                    console.log("listViewComponet, on listViewComponent complete")
                }
            }
        }
    }
    
    Connections {
        target: locationProvider
        
        onFetchProvinceSucceed: {
            console.log("qml -- onFetchProvinceSucceed");
            hideBusyIndicator(0);
        }
        
        onFetchProvinceFailed: {
            console.log("qml -- onFetchProvinceSucceed");
            hideBusyIndicator(1);
        }
    }
    
    LocationResult {
        id: locationResult
    }
    
    function hideBusyIndicator(shouldShowErrorPage) {
        console.log("qml -- hideBusyIndicator");
        runningBusyIndicator = 0;
        
        signalBusyIndicatorHide();
        
        if (shouldShowErrorPage) {
            pageLoader.sourceComponent = errorPage;
        } else {
            pageLoader.sourceComponent = listViewComponent;
        }
    }
}
