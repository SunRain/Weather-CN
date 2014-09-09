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
    qml/pages/Foo.qml \
    weather_templet \
    qml/images/wind.png \
    qml/images/w30.png \
    qml/images/w18.png \
    qml/images/w17.png \
    qml/images/w16.png \
    qml/images/w15.png \
    qml/images/w13_14.png \
    qml/images/w11_12.png \
    qml/images/w10.png \
    qml/images/w9.png \
    qml/images/w8.png \
    qml/images/w7.png \
    qml/images/w5_6.png \
    qml/images/w4.png \
    qml/images/w3.png \
    qml/images/w2_s.png \
    qml/images/w2_m.png \
    qml/images/w1_s.png \
    qml/images/w1_m.png \
    qml/images/right_arrow.png \
    qml/images/one_round.png \
    qml/images/left_arrow.png \
    qml/images/l.png \
    qml/images/humidity.png \
    qml/images/h.png \
    qml/images/air.png \
    qml/images/add.png \
    qml/images/01.png \
    qml/js/lunar.js \
    qml/js/Utils.js

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

