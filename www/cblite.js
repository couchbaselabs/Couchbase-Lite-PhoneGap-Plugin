module.exports = {
    getURL : function(callback) {
         // use node.js style error reporting (first argument)
         cordova.exec(function(url){
            callback(false, url);
         }, function(err) {
            callback(err);
        }, "CBLite", "getURL", []);
    }
}
