var Promise = require('./promise.js');

var Deferred = function () {
    this.promise = new Promise();
};

Deferred.prototype.resolve = function (obj) {
    var promise = this.promise;
    var handler;

    while ((handler = promise.queue.shift())) {
        if (handler && handler.fulfilled) {
            var ret = handler.fulfilled(obj);
            if (ret && ret.isPromise) {
                ret.queue = promise.queue;
                this.promise = ret;
                return;
            }
        }       
    }
};

Deferred.prototype.reject = function (err) {
    var promise = this.promise;
    var handler;

    while ((handler = promise.queue.shift())) {
        if (handler && handler.error) {
            var ret = handler.error(err);
            if (ret && ret.isPromise) {
                ret.queue = promise.queue;
                this.promise = ret;
                return;
            }
        }
    }
};

Deferred.prototype.callback = function () {
    var that = this;

    return function (err, file) {
        if (err) {
            console.log(err);
            return that.reject(err);
        }

        that.resolve(file);
    };
};

module.exports = Deferred;