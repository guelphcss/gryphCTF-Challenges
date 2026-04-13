const express = require("express");
const app = express();
const PORT = 3000;
const path = require("path");
const sqlite3 = require("sqlite3").verbose();

app.use(express.static(path.join(__dirname, "public")));
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.get("/commanders_quarters", (req, res) => {
  const timeHeader = (req.headers["time"] || "").toLowerCase();
  const userAgent = req.headers["user-agent"] || "";

  if (userAgent !== "guard") {
    return res
      .status(403)
      .send(
        "<h1>403 Forbidden</h1><p> You have no clearance to enter the castle.</p>",
      );
  }

  if (!timeHeader) {
    return res
      .status(400)
      .send("<h1>400 Bad Request</h1><p>Error: Wrong time to strike.</p>");
  }

  const i_twoam = /^(02:00|2:00|0200|2am|02:00am)$/.test(timeHeader);

  if (i_twoam) {
    return res.send(`
            <div>
                <h1>Mission Complete.</h1>
                <p>Flag: gryphCTF{alWays_sp00f_s3cur1ty}</p>
            </div>
        `);
  }

  return res
    .status(400)
    .send("<h1>400 Bad Request</h1><p>Error: Wrong time to strike.</p>");
});

app.post("/warwick/apothecary.html/submit", (req, res) => {
  const i_data = req.body.item;
  const db = new sqlite3.Database("./database.db", sqlite3.OPEN_READONLY);

  const query = `SELECT quantity FROM apothecary_shop_tb WHERE item_name = '${i_data}'`;

  db.get(query, (err, row) => {
    let data = "";

    if (err) {
      data += `Error: ${err.message}`;
    } else if (row) {
      const key = Object.keys(row)[0];
      data += `Result: ${row[key]}`;
    } else {
      data += `Result: Item not found.`;
    }

    res.json(data);
    db.close();
  });
});

app.post("/warwick/baker.html/submit", (req, res) => {
  const i_data = req.body.item;
  const db = new sqlite3.Database("./database.db", sqlite3.OPEN_READONLY);

  const query = `SELECT quantity FROM baker_shop_tb WHERE item_name = '${i_data}'`;

  db.get(query, (err, row) => {
    let data = "";

    if (err) {
      data += `Error: ${err.message}`;
    } else if (row) {
      const key = Object.keys(row)[0];
      data += `Result: ${row[key]}`;
    } else {
      data += `Result: Item not found.`;
    }

    res.json(data);
    db.close();
  });
});

app.post("/warwick/blacksmith.html/submit", (req, res) => {
  const i_data = req.body.item;
  const db = new sqlite3.Database("./database.db", sqlite3.OPEN_READONLY);

  const query = `SELECT quantity FROM blacksmith_shop_tb WHERE item_name = '${i_data}'`;

  db.get(query, (err, row) => {
    let data = "";

    if (err) {
      data += `Error: ${err.message}`;
    } else if (row) {
      const key = Object.keys(row)[0];
      data += `Result: ${row[key]}`;
    } else {
      data += `Result: Item not found.`;
    }

    res.json(data);
    db.close();
  });
});

app.post("/warwick/florist.html/submit", (req, res) => {
  const i_data = req.body.item;
  const db = new sqlite3.Database("./database.db", sqlite3.OPEN_READONLY);

  const query = `SELECT quantity FROM florist_shop_tb WHERE item_name = '${i_data}'`;

  db.get(query, (err, row) => {
    let data = "";

    if (err) {
      data += `Error: ${err.message}`;
    } else if (row) {
      const key = Object.keys(row)[0];
      data += `Result: ${row[key]}`;
    } else {
      data += `Result: Item not found.`;
    }

    res.json(data);
    db.close();
  });
});

app.post("/warwick/pub.html/submit", (req, res) => {
  const i_data = req.body.item;
  const db = new sqlite3.Database("./database.db", sqlite3.OPEN_READONLY);

  const query = `SELECT quantity FROM pub_shop_tb WHERE item_name = '${i_data}'`;

  db.get(query, (err, row) => {
    let data = "";

    if (err) {
      data += `Error: ${err.message}`;
    } else if (row) {
      const key = Object.keys(row)[0];
      data += `Result: ${row[key]}`;
    } else {
      data += `Result: Item not found.`;
    }

    res.json(data);
    db.close();
  });
});

app.post("/warwick/tailor.html/submit", (req, res) => {
  const i_data = req.body.item;
  const db = new sqlite3.Database("./database.db", sqlite3.OPEN_READONLY);

  const query = `SELECT quantity FROM tailor_shop_tb WHERE item_name = '${i_data}'`;

  db.get(query, (err, row) => {
    let data = "";

    if (err) {
      data += `Error: ${err.message}`;
    } else if (row) {
      const key = Object.keys(row)[0];
      data += `Result: ${row[key]}`;
    } else {
      data += `Result: Item not found.`;
    }

    res.json(data);
    db.close();
  });
});

app.post("/warwick/23_Cherry_Lane.html/submit", (req, res) => {
  const msg = (req.body.message || "").toLowerCase();
  const userAgent = (req.headers['user-agent'] || "").toLowerCase();
  
  let c_knives = msg.includes('knives');
  let c_lp = msg.includes('lockpick');
  let response = "";

  if((c_knives || c_lp) && userAgent == 'blacksmith'){
    response += "Sure... [You apprehended the thief!] gryphCTF{n0_cyb3r_cr1m3_all0w3d}"
  }else if (c_knives || c_lp){
    response += "You got the stuff... Wait... Who are you? Leave now!"
  }else if (userAgent == 'blacksmith'){
    response += "Oh hey, its you, you don\'t have the stuff? What are you even doing here."
  }else{
    response += "What? Who are you? I don\'t need any of that. Leave before I make you."
  }

  res.json(response)
});


app.listen(PORT, () => {
  console.log(`Abducted Art running on http://localhost:${PORT}`);
});
