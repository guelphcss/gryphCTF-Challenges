const express = require('express');
const app = express();
const PORT = 3000;
const path = require('path');


app.use(express.static(path.join(__dirname, 'public')));

app.get('/robots.txt', (req, res) => {
    const userAgent = (req.headers['user-agent'] || '').toLocaleLowerCase();

    if (userAgent.includes('guard')) {
        res.type('text/plain');
        res.send("User-agent: guard/1.0\nAllow: /commanders_quarters\n\n# The guards sometimes get tired and DEAH off to bed at 2AM.");
    } else {
        res.type('text/plain');
        res.send("User-agent: *\nDisallow: /admin\nDisallow: /config\n\n# WlVKVTogWGtzdWJrIHN5bS56ZHo=");
    }
});

app.get('/commanders_quarters', (req, res) => {
    const timeHeader = (req.headers['time'] || '').toLowerCase();
    const userAgent = req.headers['user-agent'] || '';

    if (userAgent !== 'guard') {
        return res.status(403).send("<h1>403 Forbidden</h1><p> You have no clearance to enter the castle.</p>");
    }

    if (!timeHeader) {
        return res.status(400).send("<h1>400 Bad Request</h1><p>Error: Wrong time to strike.</p>");
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
    
    return res.status(400).send("<h1>400 Bad Request</h1><p>Error: Wrong time to strike.</p>");
});

app.listen(PORT, () => {
    console.log(`Castle Culling running at http://localhost:${PORT}`);
});