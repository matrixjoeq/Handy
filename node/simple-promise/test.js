var fs = require('fs');
var Deferred = require('./deferred.js');

var readFile = function (file, encoding) {
    var deferred = new Deferred();
    fs.readFile(file, encoding, deferred.callback());
    return deferred.promise;
};

readFile('file1.txt', 'utf8').then(function (content) {
    console.log(content);
    return readFile(content.trim(), 'utf8');
}).then(function (content) {
    console.log(content);
});