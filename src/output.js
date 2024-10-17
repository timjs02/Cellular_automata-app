const http = require('http');
const fs = require('fs');
const path = require('path');

// use video.js to play the video??

const hostname = '127.0.0.1';
const port = 2999;

// Relative path to the video file
/*
const relPath = '/../ext/animation.mov';
const filePath = path.join(__dirname, relPath);
*/

// HTML to load the video file
const html = "./src/index.html";

const html_fs = fs.readFileSync(html, 'utf8', function(err, data) { 
    if (err) {
        console.log(`Error reading file: ${err}`);
    }
    return data;
});

// Create an HTTP server to serve the video file
const server = http.createServer(function(req, res) {
    console.log('Received request: ' + req.url);
    
    // Load the video through a html page
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(html_fs);
    res.end();
    
    // Load the video directly into the response
    /*const stat = fs.statSync(filePath);
    
    res.writeHead(200, {
        'Content-Type': 'video/quicktime',
        'Content-Length': stat.size
    });
    
    const readStream = fs.createReadStream(filePath);
    readStream.pipe(res);
    */
    
    req.on('close', () => {
        server.close(() => {
            console.log('Server closed');
        });
    });
});

// Start the server
try {
    server.listen(port, hostname, function() {
        console.log(`Server listening at http://${hostname}:${port}/`);
    });
} catch (error) {
    console.log(`Error starting server: ${error}`);
}
