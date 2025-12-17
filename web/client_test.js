const io = require("socket.io-client");
const socket = io("http://localhost:3000");

socket.on("connect", () => {
  console.log("Connected to server");
  socket.emit("start-session");
});

socket.on("terminal-output", (data) => {
  console.log("Received data:", data);
  // Veri geldiyse test başarılıdır, çıkabiliriz.
  if (data.length > 0) process.exit(0);
});

socket.on("disconnect", () => {
  console.log("Disconnected");
});

setTimeout(() => {
    console.log("Timeout waiting for data");
    process.exit(1);
}, 5000);
