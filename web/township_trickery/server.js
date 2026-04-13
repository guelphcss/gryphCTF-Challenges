const express = require("express");
const { visitGrievance } = require("./bot");

const app = express();
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

const grievances = {};

function checkLocalResident(req, res, next) {
  const xff = req.headers["x-forwarded-for"] || "";

  if (xff === "127.0.0.1" || xff === "localhost") {
    next();
  } else {
    res.status(403).send(`
            <body style="color: red; text-align: center; margin-top: 10%;">
            <h1>Halt!</h1>
            <p>Only verified residents of the LOCAL township may enter the Township.</p>
            <!-- PLEASE DON'T QUxMT1cgRk9SV0FSRElORw== -->
            </body>
        `);
  }
}

app.get("/", checkLocalResident, (req, res) => {
  res.send(`
        <body style="text-align: center;">
        <h1>Township Square</h1>
        <p>Welcome, resident. The Township is currently taking complaints.</p>
        <br>
        <div style="background: #2d2d2d; padding: 20px; display: inline-block; border: 1px solid #555;">
            <h3 style="color: white;">Submit a Grievance</h3>
            <form action="/submit" method="POST">
                <textarea name="complaint" rows="5" cols="50" placeholder="State your business (HTML allowed)..."></textarea><br><br>
                <button type="submit" style="padding: 10px; background: #5c0000; color: white; cursor: pointer;">Submit to Township</button>
            </form>
        </div>
        </body>
    `);
});

app.post("/submit", checkLocalResident, (req, res) => {
  const complaint = req.body.complaint;
  if (!complaint) return res.send("Complaint cannot be empty.");

  const id = Math.random().toString(36).substring(2, 10);
  grievances[id] = complaint;

  visitGrievance(id);

  res.send(`
        <body style="color: #4CAF50; text-align: center;">
        <h2>Grievance Submitted!</h2>
        <p>The Township is reviewing your complaint right now...</p>
        <br>
        <a href="/" style="color: lightblue;">Submit another</a>
        </body>
    `);
});

app.get("/admin/review/:id", (req, res) => {
  const complaint = grievances[req.params.id] || "No complaint found.";

  res.send(`
        <html>
        <body>
            <h1>Township Review Panel</h1>
            <p><strong>Complaint Record:</strong></p>
            <div id="complaint-body">${complaint}</div>
        </body>
        </html>
    `);
});

app.listen(3000, () => {
  console.log("Township Trickery listening on port 3000");
});
