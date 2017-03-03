var Deferred = require('./deferred.js');

var PromiseAPI = function (method) {
    return function () {
        var deferred = new Deferred();
        var args = Array.prototype.slice.call(arguments, 0);
        args.push(deferred.callback());
        method.apply(null, args);
        return deferred.promise;
    };
};

module.exports = PromiseAPI;