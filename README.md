# LIVE Distance Monitor

An IoT-based real-time distance monitoring system using ESP32, HC-SR04 ultrasonic sensor, Node.js, RabbitMQ, Docker, and a live web dashboard.

---

## Features

- ESP32 ultrasonic sensor monitoring
- Real-time dashboard updates
- RabbitMQ message queue integration
- Node.js backend API
- Dockerized RabbitMQ
- WebSocket live communication
- Wi-Fi based IoT system

---

## Technologies Used

- ESP32
- HC-SR04 Ultrasonic Sensor
- Arduino IDE
- Node.js
- Express.js
- Socket.IO
- RabbitMQ
- Docker
- HTML/CSS/JavaScript

---

## System Architecture

ESP32 → Node.js Backend → RabbitMQ → Live Dashboard

---

## Project Structure

```text
LIVE-Distance-Monitor/
│
├── backend/
│   ├── server.js
│   └── package.json
│
├── dashboard/
│   └── dashboard.html
│
├── esp32/
│   └── esp32_ultrasonic_iot.ino
│
└── README.md
```

---

## Setup Instructions

### Clone Repository

```bash
git clone https://github.com/harshath-mohomed/LIVE-Distance-Monitor.git
```

---

### Install Backend Dependencies

```bash
cd backend
npm install
```

---

### Start RabbitMQ

```bash
docker run -d \
--hostname rabbitmq \
--name rabbitmq \
-p 5672:5672 \
-p 15672:15672 \
rabbitmq:3-management
```

RabbitMQ Dashboard:
http://localhost:15672

Username:
guest

Password:
guest

---

### Run Backend

```bash
node server.js
```

---

### Open Dashboard

Open:

```text
dashboard/dashboard.html
```

---

### Upload ESP32 Code

1. Open Arduino IDE
2. Select ESP32 Dev Module
3. Select correct COM/ttyUSB port
4. Upload code

---

## Future Improvements

- Database logging
- React frontend
- Mobile notifications
- Multiple sensors
- AI analytics
- Cloud deployment

---

## Author

Your Name