var Promise = function () {
    this.queue = [];
    this.isPromise = true;
};

Promise.prototype.then = function (fulfilledHandler, errorHandler) {
    var handler = {};

    if (typeof fulfilledHandler == 'function') {
        handler.fulfilled = fulfilledHandler;
    }

    if (typeof errorHandler == 'function') {
        handler.error = errorHandler;
    }

    this.queue.push(handler);

    return this;
};

module.exports = Promise;
