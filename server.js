const express = require("express");
const cors = require("cors");
const { exec } = require("child_process");

const app = express();
app.use(cors());
app.use(express.json());

let users = [];
let bookings = [];

let resources = [
  { id: 1, name: "Lab 1", type: "Lab" },
  { id: 2, name: "Lab 2", type: "Lab" },
  { id: 3, name: "Classroom 101", type: "Classroom" },
  { id: 4, name: "Classroom 102", type: "Classroom" }
];

app.post("/register", (req, res) => {
  const { name, email, password } = req.body;

  let exist = users.find(u => u.email === email);
  if (exist) return res.send("User already registered");

  users.push({ name, email, password });
  res.send("Register successful");
});

app.post("/login", (req, res) => {
  const { email, password } = req.body;

  let user = users.find(u => u.email === email && u.password === password);
  if (!user) return res.send("Invalid email or password");

  res.send("Login successful");
});

app.get("/resources", (req, res) => {
  res.json(resources);
});

app.post("/book", (req, res) => {
  const { name, resourceId, date, startHour, endHour } = req.body;

  let conflict = bookings.find(b =>
    b.resourceId == resourceId &&
    b.date == date &&
    !(endHour <= b.startHour || startHour >= b.endHour)
  );

  if (conflict) return res.send("Resource already booked");

  bookings.push({ name, resourceId, date, startHour, endHour });
  res.send("Booking successful");
});

app.get("/bookings", (req, res) => {
  res.json(bookings);
});

app.get("/mst", (req, res) => {
  exec("g++ mst.cpp -o mst && mst", (err, stdout) => {
    if (err) return res.send("C++ MST error");
    res.send(stdout);
  });
});

app.listen(3000, () => {
  console.log("Backend running on http://localhost:3000");
});
app.listen(3000, () => {
  console.log("Backend running on http://localhost:3000");
});