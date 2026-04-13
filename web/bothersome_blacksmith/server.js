const express = require('express');
const cookieParser = require('cookie-parser');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(express.json());
app.use(cookieParser());

app.use((req, res, next) => {
    if (!req.cookies.session) {
        res.cookie('session', 'Z3Vlc3Q=', { 
            httpOnly: false, 
            path: '/',
            maxAge: 900000 
        });
    }
    next();
});

app.use(express.static(path.join(__dirname, 'public')));

// simple two layer step to this, requires cookie to be modified and content type to be JSON
app.post('/api/submit', (req, res) => {
    const sessionCookie = req.cookies.session;

    if (!sessionCookie) {
        return res.status(401).json({ message: "I'm hungry." });
    }

    const decoded = Buffer.from(sessionCookie, 'base64').toString('utf-8');
    
    if (decoded !== 'admin') {
        return res.status(403).json({ 
            message: `Not my favourite cookie, bring something better.` 
        });
    }

    if (req.headers['content-type'] !== 'application/json') {
        return res.status(415).json({ message: "What are you talking about?" });
    }

    res.json({ 
        message: "Fine, I'll help you.", 
        flag: "gryphCTF{shArp3n3d_sw0rds_4r3_hard_t0_g3t}" 
    });
});

app.use(express.static('public'));

app.listen(PORT, () => {
    console.log(`Bothersome Blacksmith running at http://localhost:${PORT}`);
});