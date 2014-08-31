import QtQuick 2.0
import Sailfish.Silica 1.0
import com.sunrain.magicweather 1.0

Page {
    id: cityPage
    property string searchString
    property int runningBusyIndicator: 1
    property string clickedCityID
    property string clickedTownID
    property string clickItemDisplayName

    property LocationProvider locationProvider
    property WeatherProvider weatherProvider

    signal signalBusyIndicatorHide()

    onSignalBusyIndicatorHide: {
        console.log("bbb qml -- onSignalBusyIndicatorHide");
    }

    Component.onCompleted: {
        console.log("bbb qml -- on cityPage Completed for city id " + clickedCityID + "  " + clickItemDisplayName);
        //locationProvider.startFetchCity(clickedCityID, clickItemDisplayName)


    }
    /*Component.onStatusChanged: {

    }*/

    Loader {
        id:pageLoader
        anchors.fill: parent
    }

    /*Column {
        id: headerContainer
        width: cityPage.width
        PageHeader {
            title: clickItemDisplayName //qsTr("Province")
        }
    }*/

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

    /*TouchInteractionHint {
        id: horizontalFlick
        loops: Animation.Infinite
        anchors.verticalCenter: parent.verticalCenter
    }
    InteractionHintLabel {
        anchors.bottom: parent.bottom
        Behavior on opacity { FadeAnimation { duration: 1000 } }
        text: qsTr("Flick left to to previous")
    }*/

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
            width: cityPage.width
            PageHeader {
                id:pageHeader
                title: clickItemDisplayName
            }

            SilicaListView {
                anchors.fill: parent
                currentIndex: -1 // otherwise currentItem will steal focus

                header:  Item {
                    id: header
                    width: cityPage.width//.width
                    height: pageHeader.height//cityPage.height//headerContainer.height

                    Component.onCompleted: {
                        headerContainer.parent = header
                        console.log("bbbb listViewComponet, on header complete")
                    }
                }

                model: locationProvider.getCityList

                delegate: BackgroundItem{

                    Label {
                        //x: searchField.textLeftMargin
                        x: Theme.paddingLarge
                        width: cityPage.width-Theme.paddingLarge
                        anchors.verticalCenter: parent.verticalCenter
                        //color: searchString.length > 0 ? (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
                        //                                : (highlighted ? Theme.highlightColor : Theme.primaryColor)
                        textFormat: Text.StyledText
                        text: model.modelData.displayText
                    }

                    onClicked: {
                        clickedTownID = model.modelData.id;
                        clickItemDisplayName = model.modelData.displayText
                        console.log("bbbb click item num <" + clickedTownID +">")
                        console.log(model.modelData.displayText)


                        pageStack.push(Qt.resolvedUrl("TownPage.qml"),{
                                           "clickedTownID":clickedTownID,
                                           "clickItemDisplayName":clickItemDisplayName,
                                           "locationProvider":locationProvider,
                                           "weatherProvider":weatherProvider})

                        locationProvider.startFetchTown(clickedTownID,clickItemDisplayName)
                    }
                }

                VerticalScrollDecorator {}

                Component.onCompleted: {
                    console.log("bbbb listViewComponet, on listViewComponent complete")
                }
            }
        }
    }

    Connections {
        target: locationProvider
        onFetchCitySucceed: {
            console.log("bbb qml -- onFetchCitySucceed");
            hideBusyIndicator(0);
        }

        onFetchCityFailed: {
            console.log("bbbb qml -- onFetchCityFailed");
            hideBusyIndicator(1);
        }
    }

    LocationResult {
        id: locationResult
    }


    function hideBusyIndicator(shouldShowErrorPage) {
        console.log("bbbb qml -- hideBusyIndicator");
        runningBusyIndicator = 0;

        signalBusyIndicatorHide();

        if (shouldShowErrorPage) {
            pageLoader.sourceComponent = errorPage;
        } else {
            pageLoader.sourceComponent = listViewComponent;
        }
        if (pageLoader.status == Loader.Ready) {
            console.log("component had loaded");
            //startTouchInteraction();
        }
    }

    function startTouchInteraction() {
        horizontalFlick.stop()
        horizontalFlick.direction = TouchInteraction.Left
        horizontalFlick.start()
    }
}

