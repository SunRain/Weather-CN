# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = MagicWeather

CONFIG += sailfishapp

SOURCES += \
    src/ProvinceListModel.cpp \
    src/LocationProvider.cpp \
    src/WeatherInfo.cpp \
    src/WeatherProvider.cpp \
    src/main.cpp \
    src/Utils.cpp

OTHER_FILES += qml/MagicWeather.qml \
    qml/cover/CoverPage.qml \
    qml/pages/SecondPage.qml \
    rpm/MagicWeather.changes.in \
    rpm/MagicWeather.spec \
    rpm/MagicWeather.yaml \
    translations/*.ts \
    MagicWeather.desktop \
    qml/pages/InfoPage.qml \
    qml/pages/ProvincePage.qml \
    qml/pages/CityPage.qml \
    qml/pages/TownPage.qml \
    translations/MagicWeather-zh_CN.ts \
    qml/pages/Foo.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += \
    translations/MagicWeather.ts
    translations/MagicWeather-de.ts
    translations/MagicWeather-zh_CN.ts

HEADERS += \
    src/ProvinceListModel.h \
    src/LocationProvider.h \
    src/WeatherInfo.h \
    src/WeatherProvider.h \
    src/Utils.h

RESOURCES +=

