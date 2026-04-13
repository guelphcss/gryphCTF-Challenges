const sqlite3 = require("sqlite3").verbose();
const db = new sqlite3.Database("./database.db");

db.serialize(() => {
  db.run(`CREATE TABLE IF NOT EXISTS apothecary_shop_tb (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        item_name TEXT NOT NULL, 
        quantity INTEGER NOT NULL,
        addr TEXT NOT NULL
    )`);

  db.run(`CREATE TABLE IF NOT EXISTS baker_shop_tb (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        item_name TEXT NOT NULL, 
        quantity INTEGER NOT NULL,
        addr TEXT NOT NULL
    )`);

  db.run(`CREATE TABLE IF NOT EXISTS blacksmith_shop_tb (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        item_name TEXT NOT NULL, 
        quantity INTEGER NOT NULL,
        addr TEXT NOT NULL
    )`);

  db.run(`CREATE TABLE IF NOT EXISTS florist_shop_tb (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        item_name TEXT NOT NULL, 
        quantity INTEGER NOT NULL,
        addr TEXT NOT NULL
    )`);

  db.run(`CREATE TABLE IF NOT EXISTS pub_shop_tb (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        item_name TEXT NOT NULL, 
        quantity INTEGER NOT NULL,
        addr TEXT NOT NULL
    )`);

  db.run(`CREATE TABLE IF NOT EXISTS tailor_shop_tb (
        id INTEGER PRIMARY KEY AUTOINCREMENT, 
        item_name TEXT NOT NULL, 
        quantity INTEGER NOT NULL,
        addr TEXT NOT NULL
    )`);

  const bl_insert = db.prepare(
    "INSERT INTO blacksmith_shop_tb (item_name, quantity, addr) VALUES (?, ?, ?)",
  );

  // Blacksmith
  bl_insert.run("Iron Sword", 15, "12_Castle_Guard_Rd");
  bl_insert.run("Steel Shield", 8, "12_Castle_Guard_Rd");
  bl_insert.run("Iron Arrows", 100, "12_Castle_Guard_Rd");
  bl_insert.run("Horseshoes", 24, "5_Stable_Way");

  // sus blacksmith
  bl_insert.run("Small Knives", 15, "23_Cherry_Lane");
  bl_insert.run("Lockpicks", 5, "23_Cherry_Lane");

  const t_insert = db.prepare(
    "INSERT INTO tailor_shop_tb (item_name, quantity, addr) VALUES (?, ?, ?)",
  );
  t_insert.run("Dark Cloak", 2, "23_Cherry_Lane");

  const a_insert = db.prepare(
    "INSERT INTO apothecary_shop_tb (item_name, quantity, addr) VALUES (?, ?, ?)",
  );
  const ba_insert = db.prepare(
    "INSERT INTO baker_shop_tb (item_name, quantity, addr) VALUES (?, ?, ?)",
  );
  const f_insert = db.prepare(
    "INSERT INTO florist_shop_tb (item_name, quantity, addr) VALUES (?, ?, ?)",
  );
  const p_insert = db.prepare(
    "INSERT INTO pub_shop_tb (item_name, quantity, addr) VALUES (?, ?, ?)",
  );

  const shops = {
    apothecary: {
      db: a_insert,
      items: [
        "Healing Potion",
        "Mana Potion",
        "Mandrake Root",
        "Bandages",
        "Sleep Syrup",
        "Antidote",
      ],
    },
    baker: {
      db: ba_insert,
      items: [
        "Loaf of Bread",
        "Sweet Roll",
        "Meat Pie",
        "Apple Tart",
        "Scone",
        "Rye Bread",
      ],
    },
    florist: {
      db: f_insert,
      items: [
        "Rose Bouquet",
        "Spider Lily",
        "Lily",
        "Tulip",
        "Wildflower Wreath",
        "Dried Herbs",
      ],
    },
    pub: {
      db: p_insert,
      items: [
        "Keg of Ale",
        "Bottle of Mead",
        "Bowl of Stew",
        "Roasted Boar",
        "Spiced Wine",
        "Croquettes",
        "Soup",
      ],
    },
    tailor: {
      db: t_insert,
      items: [
        "Linen Shirt",
        "Leather Belt",
        "Wool Tunic",
        "Silk Scarf",
        "Winter Cloak",
        "Dark Cloak",
      ],
    },
  };

  const addresses = [
    "12_Baker St",
    "55_Main_St",
    "99_Kings_Road",
    "1_Castle_View",
    "4_Muddy_Lane",
    "17_High_St",
    "8_Cobblestone_Path",
    "42_River_Walk",
    "3_Market_Square",
    "11_Lantern_Alley",
    "7_Griffin_Way",
    "21_Beggars_Lane",
  ];

  const getRandom = (arr) => arr[Math.floor(Math.random() * arr.length)];

  for (const [_, items] of Object.entries(shops)) {
    for (let i = 0; i < 25; i++) {
      const randomItem = getRandom(items.items);
      const randomQty = Math.floor(Math.random() * 6) + 1;
      const randomAddr = getRandom(addresses);

      items.db.run(randomItem, randomQty, randomAddr);
    }
  }

  bl_insert.finalize();
  t_insert.finalize();
  a_insert.finalize();
  ba_insert.finalize();
  f_insert.finalize();
  p_insert.finalize();
});

db.close(() => {
  console.log(
    "Abducted Art db created. Randomized All shops but blacksmith, and part if tailor.",
  );
});
