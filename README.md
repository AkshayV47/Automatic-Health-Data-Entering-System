# Automatic-Health-Data-Entering-System

🏥 Automatic Health Data Entry System using ESP8266
📌 Project Overview

The Automatic Health Data Entry System is an IoT-based healthcare solution designed to reduce patient queues in hospitals by automatically measuring and recording basic health parameters. The system captures body weight, height, and heart rate without manual intervention and uploads the data digitally.

This solution improves hospital efficiency, minimizes human error, and enables faster patient check-in for medical consultations.

🎯 Key Features

⚖️ Automatic weight measurement using load/weight sensor

❤️ Real-time heart rate monitoring

📏 Height detection using ultrasonic sensor

🌐 WiFi-enabled data processing with ESP8266

📊 Digital health data entry

⏱️ Reduces waiting time and patient queues

🏥 Suitable for hospitals and clinics

🛠️ Components Used

ESP8266 (NodeMCU)

Weight Sensor (Load Cell)

Heart Rate Sensor

Ultrasonic Sensor (for height measurement)

Power Supply Module

Display / Cloud Dashboard (optional)

Connecting Wires & Resistors

⚙️ Working Principle

The patient stands on the system platform.

The weight sensor measures the body weight.

The ultrasonic sensor calculates height by measuring the distance from the head.

The heart rate sensor records pulse rate.

The ESP8266 collects all sensor data and processes it.

The measured health parameters are automatically entered into a digital system.

The data can be accessed by doctors before consultation, reducing manual check-up time.

🔁 System Flow
Patient Entry
     ↓
Weight Sensor → ESP8266
Heart Rate Sensor → ESP8266
Ultrasonic Sensor → ESP8266
     ↓
Automatic Health Data Entry
     ↓
Doctor Consultation

🌍 Applications

Hospitals & clinics

OPD registration counters

Smart healthcare systems

Rural health centers

Automated patient screening

🚀 Advantages

Reduces patient waiting time

Minimizes manual data entry

Improves hospital workflow

Cost-effective automation

Scalable for multi-patient systems

📌 Future Enhancements

Cloud-based patient record storage

Integration with hospital management systems

QR / RFID-based patient identification

Additional sensors (BP, SpO₂, temperature)

Mobile app for doctors and nurses

📂 Repository Contents

ESP8266 firmware code

Circuit diagram

Sensor calibration details

System flowchart

Project documentation
