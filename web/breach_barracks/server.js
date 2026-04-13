const express = require('express');
const { MongoClient } = require('mongodb');
const jwt = require('jsonwebtoken');
const cookieParser = require('cookie-parser');
const crypto = require('crypto');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, "public")));
app.use(express.json()); 
app.use(cookieParser());


const MONGO_URI = process.env.MONGO_URI || 'mongodb://localhost:27017/barracks';
const JWT_SECRET = process.env.JWT_SECRET || 'excalibur';

let db;

MongoClient.connect(MONGO_URI)
  .then(client => {
    db = client.db('barracks');
    console.log("Connected to MongoDB");
    initializeDatabase();
  })
  .catch(err => console.error("MongoDB connection error:", err));

async function initializeDatabase() {
  const collection = db.collection('soldiers');
  const count = await collection.countDocuments();
  
  if (count === 0) {
    console.log("Loading Barracks Database from JSON...");
    
    const rawData = fs.readFileSync('./database.json');
    const soldiersData = JSON.parse(rawData);
    
    const soldiers = soldiersData.map(soldier => {
      let role = 'soldier';
      let note = soldier.commanders_note;

      if (soldier.name === 'Arthur') {
        role = 'commander';
        note += " [CLASSIFIED] WAR PLANS: uhh attack here, attack there, idk! FLAG: gryphCTF{1nf1ltrat3_and_3xf1ltrat3}";
      }

      return {
        uuid_hash: soldier.uuid,
        username: soldier.name,
        password: `pass_${crypto.randomBytes(4).toString('hex')}`,
        role: role,
        note: note
      };
    });

    await collection.insertMany(soldiers);
    console.log(`${soldiers.length} Soldiers mobilized from JSON!`);
  }
}

app.post('/login', async (req, res) => {
  try {
    const user = await db.collection('soldiers').findOne(req.body);

    if (user) {
      const token = jwt.sign(
        { username: user.username, role: user.role }, 
        JWT_SECRET, 
        { expiresIn: '1h' }
      );
      
      res.cookie('token', token, { httpOnly: true });
      res.json({ success: true, redirect: `/profile?uuid=${user.uuid_hash}` });
    } else {
      res.status(401).json({ error: "Invalid credentials" });
    }
  } catch (error) {
    res.status(500).json({ error: "Server Error", details: error.message });
  }
});

app.get('/profile', async (req, res) => {
  const token = req.cookies.token;
  const targetUuid = req.query.uuid;

  if (!token || !targetUuid) {
    return res.status(403).send("Missing token or UUID.");
  }

  try {
    const decoded = jwt.verify(token, JWT_SECRET);
    const targetProfile = await db.collection('soldiers').findOne({ uuid_hash: targetUuid });

    if (!targetProfile) {
      return res.status(404).send("Profile not found.");
    }

    if (decoded.role === 'knight' && decoded.username !== targetProfile.username) {
      return res.status(403).send("Access Denied: You do not have the rank of commander.");
    }

    let html = `<h2>Profile: ${targetProfile.username}</h2>`;
    html += `<p>Rank: ${targetProfile.role}</p>`;
    
    if (targetProfile.role === 'commander' && decoded.role !== 'commander') {
        html += `<p>Commander's Note: [REDACTED - COMMANDER ACCESS ONLY]</p>`;
    } else if (targetProfile.role === 'commander' && decoded.role === 'commander') {
        html += `<h3 style="color:red;">Commander's Note: ${targetProfile.note}</h3>`;
    } else {
        html += `<p>Commander's Note: ${targetProfile.note}</p>`;
    }

    res.send(html);

  } catch (err) {
    res.status(401).send("Invalid Token.");
  }
});

app.listen(PORT, () => {
  console.log(`Breach Barracks listening on port ${PORT}`);
});