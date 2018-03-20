var key="";
var express = require('express');
var app = express();

app.get('/', function(req, res) {
  auth = req.get('Authorization');
  if (auth === undefined) {
    res.setHeader('WWW-Authenticate', 'Basic realm="Secure Area"');
    res.setHeader('Content-type', 'text/html');
    return res.status(401).send('no auth header received');
  } else if (auth === "Basic " + key){
    res.send("OK");
  } else {
    res.setHeader('WWW-Authenticate', 'Basic realm="Secure Area"');
    res.setHeader('Content-type', 'text/html');
    return res.status(401).send('not authenticated');
  }
});

if(process.argv.length !== 4) {
  console.log("Usage: node " + process.argv[1] + " port user:pwd");
  process.exit();
}

app.listen(parseInt(process.argv[2]));
key = Buffer.from(process.argv[3]).toString('base64');
console.log("app running at http://localhost:"+process.argv[2]);
