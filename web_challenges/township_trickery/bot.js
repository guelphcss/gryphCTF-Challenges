const puppeteer = require('puppeteer');

async function visitGrievance(id) {
    let browser;
    try {
        browser = await puppeteer.launch({
            headless: true,
            args: [
                '--no-sandbox',
                '--disable-setuid-sandbox',
                '--disable-dev-shm-usage'
            ]
        });
        
        const page = await browser.newPage();

        await page.setCookie({
            name: 'auth_token',
            value: 'Z3J5cGhDVEZ7dHIxY2tfdGgzX3Qwd25zaDFwX3dfeCQkfQ==', 
            domain: 'localhost',
            path: '/',
            httpOnly: false
        });

        console.log(`Magistrate is reviewing grievance: ${id}`);
        await page.goto(`http://localhost:3000/admin/review/${id}`, {
            waitUntil: 'networkidle2',
            timeout: 5000
        });

        await new Promise(r => setTimeout(r, 2000));

    } catch (err) {
        console.error("Bot error:", err);
    } finally {
        if (browser) await browser.close();
    }
}

module.exports = { visitGrievance };