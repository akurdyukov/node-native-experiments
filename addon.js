var addon = require('bindings')('addon');

addon(10, function(obj){
  console.log("result -> " + obj.plusOne());
});
