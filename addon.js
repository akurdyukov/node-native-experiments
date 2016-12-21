var addon = require('bindings')('addon');

var x = addon(10, function(msg){
  console.log(msg);
});

console.log(x);
