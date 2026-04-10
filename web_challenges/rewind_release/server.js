const express = require('express');
const path = require('path');

const app = express();

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

app.post('/api/vault/open', (req, res) => {
    const clientTime = new Date(req.body.local_time);
    
    if (clientTime.getFullYear() === 1347) {
        res.json({ success: true, message: "The ancient seals break... gryphCTF{t1m3_tr4v3l_1s_cl13nt_s1d3}" });
    } else {
        res.json({ success: false, message: "The vault remains sealed. It will only open in the year 1347." });
    }
});

app.listen(3000, () => {
    console.log("Rewind Release listening on port 3000");
});