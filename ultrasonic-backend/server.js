import express from "express";
import { createServer } from "http";
import { Server as SocketIOServer } from "socket.io";
import { connect } from "amqplib";

const app = express();
const server = createServer(app);
const io = new SocketIOServer(server, {
  cors: {
    origin: "*"
  }
});

app.use(express.json());

let channel;

// =====================
// RabbitMQ Connection
// =====================

async function connectRabbitMQ() {
  const connection = await connect("amqp://localhost");
  channel = await connection.createChannel();
  await channel.assertQueue("distance_queue");

  console.log("RabbitMQ Connected");
}

connectRabbitMQ();

// =====================
// ESP32 API Endpoint
// =====================

app.post("/distance", (req, res) => {
  const data = req.body;

  console.log("Distance Data:");
  console.log(data);

  // Send to RabbitMQ
  channel.sendToQueue(
    "distance_queue",
    Buffer.from(JSON.stringify(data))
  );

  // Send realtime to browser
  io.emit("distance_update", data);

  res.send("Data Received");
});

// =====================
// Start Server
// =====================

server.listen(3000, () => {
  console.log("IoT Server Running");
});