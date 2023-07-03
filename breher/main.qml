import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import io.qt.backend 1.0

ApplicationWindow {
    width: 1280
    height: 720
    Material.theme: Material.Light
    Material.primary: Material.LightBlue
    Material.accent: Material.BlueGrey

    visible: true
    title: qsTr("Breher")
    id: window

    Backend {
        id: backend

    }

    Connections {
        target: backend
        function onValveStateChanged(index,strength) {

//            if( state === 0)
//                valve_repeater.itemAt(index).children[3].text = "Opened"
//            else
//                valve_repeater.itemAt(index).children[3].text = "Closed"
             valve_repeater.itemAt(index).children[1].Material.background = Material.LightBlue


        }

        function onHeaterStateChanged(index,state) {

            if( state === 1){
                heater_repeater.itemAt(index).children[1].Material.background  = Material.Red
                heater_repeater.itemAt(index).children[2].Material.background  = Material.BlueGrey
            }
            else{
                heater_repeater.itemAt(index).children[2].Material.background  = Material.Red
                heater_repeater.itemAt(index).children[1].Material.background  = Material.BlueGrey
            }
        }

        function onSolenoidStateChanged(index,state) {

//            if( state === 1)
//                solenoid_repeater.itemAt(index).children[3].text = "Opened"
//            else
//                solenoid_repeater.itemAt(index).children[3].text = "Closed"

            if( state === 1){
                solenoid_repeater.itemAt(index).children[1].Material.background  = Material.Grey
                solenoid_repeater.itemAt(index).children[2].Material.background  = Material.BlueGrey
            }
            else{
                solenoid_repeater.itemAt(index).children[2].Material.background  = Material.Grey
                solenoid_repeater.itemAt(index).children[1].Material.background  = Material.BlueGrey
            }
        }

        function onPumpStateChanged(index,state) {

            if( state === 1){
                pump_repeater.itemAt(index).children[1].Material.background  = Material.LightGreen
                pump_repeater.itemAt(index).children[2].Material.background  = Material.BlueGrey
            }
            else{
                pump_repeater.itemAt(index).children[2].Material.background  = Material.LightGreen
                pump_repeater.itemAt(index).children[1].Material.background  = Material.BlueGrey
            }
//            if( state === 1)
//                pump_repeater.itemAt(index).children[3].text = "Started"
//            else
//                pump_repeater.itemAt(index).children[3].text = "Stopped"
        }

    }
    property int fieldHeight: window.height/(backend.getMaxNumberInSameType()+4)

    GridLayout{
        id: ownLayout
        anchors.fill: parent


        ColumnLayout
        {
            id: valves_column

            spacing: 5

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Label {
                Layout.alignment: Qt.AlignCenter

                text: "Valves"
                font.pointSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
            Image{

                Layout.alignment: Qt.AlignCenter
                source: "pics/valve.png"
                sourceSize.width: 96
                sourceSize.height: 96
            }


            Repeater{

                id: valve_repeater
                model: backend.getValveNumber()

                RowLayout {


                    required property int index

                    spacing:5
                    Layout.preferredHeight: fieldHeight
                    Label {


                        text:"  V" + (index+1) + "  "
                        Layout.alignment: Qt.AlignCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 15


                    }


                    Button{


                        Material.background: Material.LightBlue
                        id:openValve
                        text:"Set"
                        Layout.alignment: Qt.AlignCenter
                        enabled:true
                        onClicked: {
                            //open_button_background.color = "lightgreen"
                             backend.setValveStrength(index,Math.round(strength_slider.value))
                             //backend.setValveState(index,0)
                        }
                    }


                    Slider {


                        Material.background: Material.BlueGrey

                        Layout.alignment: Qt.AlignCenter
                        id: strength_slider
                        from: 0
                        value: 100
                        to: 100

                        onMoved: {
                            valve_status_label.text = Math.round(strength_slider.value).toString()
                            openValve.Material.background = Material.BlueGrey
                        }
                    }

                    Label {


                        id: valve_status_label
                        text: Math.round(strength_slider.value).toString()
                        Layout.alignment: Qt.AlignCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        Layout.maximumWidth: 15
                        Layout.minimumHeight: 15
                        font.pointSize: 15
                    }
                }
            }
        }

        ColumnLayout
        {
            id: heater_column
            spacing: 5

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Label {
                Layout.alignment: Qt.AlignCenter
                text: "Heaters"
                font.pointSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }

            Image{
                Layout.alignment: Qt.AlignCenter
                source: "pics/heater.png"
                sourceSize.width: 96
                sourceSize.height: 96
            }
            Repeater{
                id: heater_repeater
                model: backend.getHeaterNumber()

                RowLayout {

                    required property int index
                    spacing:5
                    Layout.preferredHeight: fieldHeight
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Label {

                        text:"  H" + (index+1) + "  "
                        Layout.alignment: Qt.AlignCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 15

                    }


                    Button{
                        Material.background:Material.BlueGrey
                        id:startHeater
                        text:"Start"
                        Layout.alignment: Qt.AlignCenter
                        enabled:true
                        onClicked: {
                            backend.setHeaterState(index,1)
                        }
                    }
                    Button{
                        Material.background:Material.Red
                        id:stopHeater
                        text:"Stop"
                        enabled:true
                        Layout.alignment: Qt.AlignCenter

                        onClicked: {

                            backend.setHeaterState(index,0)
                        }
                    }
//                    Label {
//                        id: heater_status_label
//                        text: "      "
//                        Layout.alignment: Qt.AlignCenter
//                        horizontalAlignment: Text.AlignHCenter
//                        verticalAlignment: Text.AlignVCenter
//                        font.pointSize: 15
//                    }
                }
            }
        }

        ColumnLayout
        {
            id: solenoid_column
            spacing: 5

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Label {
                Layout.alignment: Qt.AlignCenter
                text: "Solenoids"
                font.pointSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
            Image{
                Layout.alignment: Qt.AlignCenter
                source: "pics/tap.png"
                sourceSize.width: 96
                sourceSize.height: 96
            }

            Repeater{
                id: solenoid_repeater
                model: backend.getSolenoidNumber()

                RowLayout {

                    required property int index
                    spacing:5
                    Layout.preferredHeight: fieldHeight
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Label {

                        text:"  S" + (index+1) + "  "
                        Layout.alignment: Qt.AlignCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 15


                    }


                    Button{
                        Material.background: Material.BlueGrey
                        id:openSolenoid
                        text:"Open"
                        Layout.alignment: Qt.AlignCenter
                        enabled:true
                        onClicked: {
                            backend.setSolenoidState(index,1)
                        }
                    }
                    Button{
                        Material.background: Material.Grey
                        id:closeSolenoid
                        text:"Close"
                        enabled:true
                        Layout.alignment: Qt.AlignCenter

                        onClicked: {
                           backend.setSolenoidState(index,0)
                        }
                    }
//                    Label {
//                        id: solenoid_status_label
//                        text: "      "
//                        Layout.alignment: Qt.AlignCenter
//                        horizontalAlignment: Text.AlignHCenter
//                        verticalAlignment: Text.AlignVCenter
//                        font.pointSize: 15
//                    }
                }
            }
        }

        ColumnLayout
        {
            id: pump_column
            spacing: 5

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Label {
                Layout.alignment: Qt.AlignCenter
                text: "Pumps"
                font.pointSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
            Image{
                Layout.alignment: Qt.AlignCenter
                source: "pics/pump.png"
                sourceSize.width: 96
                sourceSize.height: 96
            }

            Repeater{
                id: pump_repeater
                model: backend.getPumpNumber()

                RowLayout {

                    required property int index
                    spacing:5
                    Layout.preferredHeight: fieldHeight
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Label {

                        text:"  P" + (index+1) + "  "
                        Layout.alignment: Qt.AlignCenter
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 15

                    }


                    Button{
                        Material.background: Material.BlueGrey
                        id:startPump
                        text:"Start"
                        Layout.alignment: Qt.AlignCenter
                        enabled:true
                        onClicked: {
                            backend.setPumpState(index,1)
                        }
                    }
                    Button{
                        Material.background: Material.LightGreen
                        id:stopPump
                        text:"Stop"
                        enabled:true
                        Layout.alignment: Qt.AlignCenter

                        onClicked: {

                            backend.setPumpState(index,0)
                        }
                    }

                }
            }
        }

        ColumnLayout
        {
            id: sensor_column

            spacing: 5

            Layout.alignment: Qt.AlignCenter| Qt.AlignHCenter

            Timer{
                id: refresh_timer

                       interval: 3000
                       running:true
                       repeat: true
                       onTriggered: {
                           rspi_label.text = "RSPI Current: " + (backend.getRaspCurrent()*1000).toFixed(2) + " mA"
                           rspi_label_voltage.text = "RSPI Voltage: " + backend.getRaspOutputVoltage().toFixed(2) + " V"

                          current_label1.text = "P1 Current: " + (backend.getPumpCurrent(0)*1000).toFixed(2)  + " mA"
                          current_label1_voltage.text  = "P1 Voltage: " + backend.getPumpOutputVoltage(0).toFixed(2)  + " V"
                          current_label2.text = "P2 Current: " + (backend.getPumpCurrent(1)*1000).toFixed(2)  + " mA"
                           current_label2_voltage.text  = "P2 Voltage: " + backend.getPumpOutputVoltage(1).toFixed(2)  + " V"
                          temp_label1.text = "H1 Temp: " + backend.getTemperature(0).toFixed(2)  + " °C"
                          temp_label2.text = "H2 Temp: " + backend.getTemperature(1).toFixed(2)  + " °C"
                       }
            }




                     Label{
                         id: rspi_label
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: rspi_label_voltage
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: current_label1
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: current_label1_voltage
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: current_label2
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: current_label2_voltage
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: temp_label1
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15


                     }
                     Label{
                         id: temp_label2
                         Layout.fillHeight: true
                         Layout.alignment: Qt.AlignCenter
                         horizontalAlignment: Text.AlignHCenter
                         verticalAlignment: Text.AlignVCenter
                         font.pointSize: 15



                     }








        }





    }

}
