/*******************************************************************************
* Copyright (c) 2015 Shawn Rutledge
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*******************************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.0

import Yat 1.0 as Yat

Window {
    id: terminalWindow
    visible: true
    width: 800
    height: 600
    color: "black"

    Yat.TerminalModel {
        id: termModel
//        onQuiescent: {
//            console.log("quiescent")
//            listView.positionViewAtEnd()
//        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        anchors.margins: 4
        model: termModel.rows
        onCountChanged: jumpToEndTimer.restart()
        delegate: Item {
            height: childrenRect.height
            width: parent.width
            property var rowModel: termModel.rows[index]
            Text {
                text: rowModel.text
                visible: !textInput.visible
                color: "beige"
            }
            TextInput {
                id: textInput
                visible: rowModel.hasOwnProperty("inputField")
                onAccepted: {
                    termModel.exec(text)
                    text = ""
                }
                width: parent.width
//                Component.onCompleted: console.log("TextInput completed")// forceActiveFocus()
                color: "white"
            }
        }
    }

    Timer {
        id: jumpToEndTimer
        interval: 100
        onTriggered: listView.positionViewAtEnd()
    }
}
