var fs = require('fs');
var PromiseAPI = require('./promise_api.js');

var readFile = PromiseAPI(fs.readFile);

readFile('file1.txt', 'utf8').then(function (content) {
    console.log(content);
    return readFile(content.trim(), 'utf8');
}).then(function (content) {
    console.log(content);
});