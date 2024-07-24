#ifndef HTML_H
#define HTML_H

// Store HTML content in PROGMEM
const char htmlContent[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Motor Controller</title>
    <style>
        .active {
            background-color: rgb(78, 78, 217);
            color: white;
            pointer-events: none;
        }
    </style>
</head>
<body style="background-color: darkslategray; color: white; margin: 3%;">
    <h1>ESP32 Motor Controller</h1>

    <div style="display: flex; flex-direction: column; gap: 20px; width: 50%; background-color: dimgray; padding: 2%;">

        <div style="margin-bottom: 20px;">
            <label style="margin: 4%;" for='speed'>Speed: <span id='speed_value'>0</span></label>
            <div style="display: flex; flex-direction: row; align-items: center; margin: 1%;">
                <input type='range' id='speed' name='speed' min='-255' max='255' value='0' oninput='updateSpeed(this.value)'>
                <button onclick="stop()" style="background-color: rgb(140, 41, 41); color: rgb(250, 243, 243); padding: 10px; margin: 10px; width: 30%;">Stop</button>
            </div>
        </div>

        <div>
            <label style="margin: 4%;" for='steering'>Steering: <span id='steering_value'>90</span></label>
            <div style="display: flex; flex-direction: row; align-items: center; margin: 1%;">
                <input type='range' id='steering' name='steering' min='20' max='160' value='90' oninput='updateSteering(this.value)'>
                <button onclick="straighten()" style="background-color: rgb(88, 88, 88); color: rgb(250, 243, 243); padding: 10px; margin: 10px; width: 30%;">Straighten</button>
            </div>
        </div>
        
    </div>

    <script>
        let socket;
    
        window.onload = function() {
            socket = new WebSocket(`ws://${window.location.hostname}/ws`);
    
            socket.onopen = function() {
                console.log('WebSocket connection established');
            };
    
            socket.onmessage = function(event) {
                console.log('Message from server:', event.data);
            };
    
            socket.onclose = function() {
                console.log('WebSocket connection closed');
            };
    
            socket.onerror = function(error) {
                console.error('WebSocket error:', error);
            };
    
            // Add keydown event listener
            window.addEventListener('keydown', handleKeyDown);
            window.addEventListener('keyup', handleKeyUp);
        };
    
        function updateSpeed(value) {
            document.getElementById('speed_value').innerText = value;
            document.getElementById('speed').value = value;
            socket.send(`speed:${value}`);
        }
    
        function updateSteering(value) {
            document.getElementById('steering_value').innerText = value;
            document.getElementById('steering').value = value;
            socket.send(`steering:${value}`);
        }
    
        function stop() {
            updateSpeed(0);
        }
    
        function straighten() {
            updateSteering(90);
        }
    
        function handleKeyDown(event) {
            switch (event.key) {
                case 'w':
                    updateSpeed(255);
                    break;
                case 's':
                    updateSpeed(-255);
                    break;
                case 'a':
                    updateSteering(160);
                    break;
                case 'd':
                    updateSteering(20);
                    break;
            }
        }
    
        function handleKeyUp(event) {
            // Optional: Stop movement when keys are released
            if (event.key === 'w' || event.key === 's') {
                updateSpeed(0);
            }
            // Optional: Straighten steering when 'a' or 'd' is released
            if (event.key === 'a' || event.key === 'd') {
                straighten();
            }
        }
    </script>
    
</body>
</html>


)rawliteral";

#endif